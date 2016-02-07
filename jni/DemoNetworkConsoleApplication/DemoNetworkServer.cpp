#include "DemoNetworkServer.hpp"

#include "DemoNetworkCommon.hpp"
#include "BroadcastSearchServer.hpp"

using namespace MPACK;
using namespace MPACK::Time;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

namespace Demo
{
	NetworkServer::NetworkServer(MPACK::Network::UDPSocket *sock, int searchPort)
		: m_sock(sock), m_searchPort(searchPort)
	{
		m_sock->EnableCRC32();
	}

	NetworkServer::~NetworkServer()
	{
	}

	int NetworkServer::Run()
	{
		BroadcastSearchServer *searchServer = new BroadcastSearchServer();

		searchServer->Init(m_searchPort);

		bool running=true;
		Network::UDPMessage msg;
		while(running)
		{
			searchServer->Update();

			while(m_sock->Poll(msg))
			{
				char buffer[BUFFER_SIZE];
				msg.Read(buffer,msg.Length());
				buffer[msg.Length()]=0;

				if(strcmp(buffer,"-quit_server")==0 || strcmp(buffer,"-quit_both")==0)
				{
					running=false;
					break;
				}

				LOGI("Recieved data, count=%d: %s",msg.Length(),buffer);
				m_sock->SendTo(msg,m_sock->lastContact);
			}
		}

		delete searchServer;

		LOGI("Server shutdown!");

		return 0;
	}
}
