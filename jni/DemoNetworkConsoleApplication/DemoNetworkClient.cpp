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

		while(1)
		{
			std::cin.getline(buffer,BUFFER_SIZE);
			msg.Clear();
			msg.Write(buffer,strlen(buffer)+1);

			if(strcmp(buffer,"-quit_both")==0)
			{
				m_sock->SendTo(msg,m_serverAddress);
				break;
			}
			if(strcmp(buffer,"-quit")==0)
			{
				break;
			}

			m_sock->SendTo(msg,m_serverAddress);

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
}
