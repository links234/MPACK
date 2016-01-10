#include "DemoNetworkClient.hpp"

#include "DemoNetworkCommon.hpp"

using namespace MPACK;
using namespace MPACK::Time;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

namespace Demo
{
	NetworkClient::NetworkClient(Network::UDPSocket *sock, Network::SocketAddress serverAddr)
		: m_sock(sock), m_serverAddress(serverAddr)
	{
	}

	NetworkClient::~NetworkClient()
	{
	}

	int NetworkClient::Run()
	{
		Network::UDPMessage	msg;

		char buffer[BUFFER_SIZE];
		pthread_t stdinThread;
		int rc = pthread_create(&stdinThread, NULL, NetworkClient::STDINThread, (void*)(this));
		if (rc)
		{
			LOGE("NetworkClient::Run() stdin pthread_create failed!");
			return 1;
		}

		while (true)
		{
			std::string cmd;
			if (MessageQueuePop(cmd))
			{
				if(cmd == "-quit_both")
				{
					msg.Clear();
					msg.Write(cmd.c_str(),cmd.size());
					m_sock->SendTo(msg,m_serverAddress);
					break;
				}
				else if(cmd == "-quit")
				{
					break;
				}

				msg.Clear();
				msg.Write(cmd.c_str(),cmd.size());

				m_sock->SendTo(msg,m_serverAddress);
			}

			while(m_sock->Poll(msg))
			{
				msg.Read(buffer,msg.Length());
				buffer[msg.Length()]=0;
				LOGI("Recieved data, count=%d: %s",msg.Length(),buffer);
			}
		}

		LOGI("Client shutdown!");

		return 0;
	}

	void *NetworkClient::STDINThread(void *param)
	{
		NetworkClient *client = (NetworkClient*)(param);

		char buffer[BUFFER_SIZE];

		while (true)
		{
			std::cin.getline(buffer,BUFFER_SIZE);

			client->MessageQueuePush(std::string(buffer));
		}

		return NULL;
	}

	void NetworkClient::MessageQueuePush(const std::string &message)
	{
		m_messageQueue.push(message);
	}

	bool NetworkClient::MessageQueuePop(std::string &message)
	{
		if (!m_messageQueue.empty())
		{
			message = m_messageQueue.front();
			m_messageQueue.pop();
			return true;
		}
		return false;
	}
}
