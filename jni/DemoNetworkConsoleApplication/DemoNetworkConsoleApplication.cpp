#include "DemoNetworkConsoleApplication.hpp"

#include "DemoNetworkCommon.hpp"
#include "DemoNetworkServer.hpp"
#include "DemoNetworkClient.hpp"

using namespace MPACK;
using namespace MPACK::Time;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

namespace Demo
{
	NetworkConsoleApplication::NetworkConsoleApplication()
	{
	}

	NetworkConsoleApplication::~NetworkConsoleApplication()
	{
	}

	bool NetworkConsoleApplication::SearchLANForServer()
	{
		const double sendDelay=0.5;
		const double timeout=5.0;

		LOGI("Automatic LAN server searching!");
		LOGI("LAN Server Search: Timeout set to %.2lf seconds", timeout);

		Network::SocketAddress	broadcastAddr;
		broadcastAddr.SetBroadcastAddress();
		broadcastAddr.SetPort(SEARCH_SERVICE_PORT);

		Network::UDPSocket *sock=new Network::UDPSocket();
		sock->SetBroadcast(true);
		sock->SetNonBlocking(true);
		if(!sock->Bind(SEARCH_SERVICE_PORT))
		{
			LOGI("LAN Server Search: Seems like we have another server running localy!");
			m_serverAddr.SetLocalhostAddress();
			m_serverAddr.SetPort(SERVER_PORT);
			delete sock;
			return true;
		}

		Timer *timeoutTimer=Timer::Create();
		Timer *sendDelayTimer=Timer::Create();

		char buffer[BUFFER_SIZE];
		Network::UDPMessage msg;

		bool serverNotFound=true;

		timeoutTimer->Start();
		int count=0;
		while(timeoutTimer->Time()<timeout && serverNotFound)
		{
			if(sendDelayTimer->Time()>sendDelay)
			{
				sendDelayTimer->Start();
				strcpy(buffer,"-check_for_server");

				msg.Clear();
				msg.Write(buffer,strlen(buffer)+1);
				sock->SendTo(msg,broadcastAddr);
				++count;
				LOGI("LAN Server Search: Send message number = %d",count);
			}

			while(sock->Poll(msg))
			{
				msg.Read(buffer,msg.Length());
				buffer[msg.Length()]=0;
				if(strcmp(buffer,"-server_online")==0)
				{
					m_serverAddr=sock->lastContact;
					m_serverAddr.SetPort(SERVER_PORT);
					serverNotFound=false;
					delete sock;
					return true;
				}
			}
		}

		delete sendDelayTimer;
		delete timeoutTimer;
		delete sock;
		return false;
	}

	void NetworkConsoleApplication::NoServerResponding()
	{
		Network::UDPSocket *sock;

		sock=new Network::UDPSocket();
		sock->SetNonBlocking(true);

		int currentPort=SERVER_PORT;
		if(!sock->Bind(currentPort))
		{
			LOGW("But server seems to be already started in local machine! - this should not happen");
			LOGI("Going in client mode!");
			++currentPort;
			while(!sock->Bind(currentPort))
			{
				++currentPort;
			}
			LOGI("Port %d is available",currentPort);
			ClientMode(sock);
		}
		else
		{
			LOGI("Server mode on, waiting for clients");
			ServerMode(sock);
		}

		delete sock;
	}

	void NetworkConsoleApplication::ServerFound()
	{
		Network::UDPSocket *sock;

		sock=new Network::UDPSocket();
		sock->SetNonBlocking(true);

		int currentPort=SERVER_PORT;
		++currentPort;
		while(!sock->Bind(currentPort))
		{
			++currentPort;
		}
		LOGI("Port %d is available",currentPort);
		ClientMode(sock);

		delete sock;
	}

	void NetworkConsoleApplication::ClientMode(Network::UDPSocket *sock)
	{
		NetworkClient *client = new NetworkClient(sock, m_serverAddr);
		client->Run();
		delete client;
	}

	void NetworkConsoleApplication::ServerMode(Network::UDPSocket *sock)
	{
		NetworkServer *server = new NetworkServer(sock, SEARCH_SERVICE_PORT);
		server->Run();
		delete server;
	}

	int NetworkConsoleApplication::Main()
	{
		Network::Wrapper::Init();

		if(SearchLANForServer())
		{
			LOGI("Server found!");
			ServerFound();
		}
		else
		{
			LOGI("No server responding!");
			NoServerResponding();
		}

		Network::Wrapper::Shutdown();
		return 0;
	}
}
