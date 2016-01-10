#include "BroadcastSearchServer.hpp"

#include "DemoNetworkCommon.hpp"

using namespace MPACK;
using namespace MPACK::Time;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

BroadcastSearchServer::BroadcastSearchServer()
	: m_sock(NULL)
{
}

BroadcastSearchServer::~BroadcastSearchServer()
{
	if (m_sock) {
		delete m_sock;
		m_sock = NULL;
	}
}

void BroadcastSearchServer::Init(int port)
{
	if (m_sock) {
		delete m_sock;
		m_sock = NULL;
	}

	m_sock=new Network::UDPSocket;
	if(!m_sock->Bind(port))
	{
		LOGE("Failed to start search service, exit!");
		return;
	}
	m_sock->SetBroadcast(true);
	m_sock->SetNonBlocking(true);
}

void BroadcastSearchServer::Update()
{
	Network::UDPMessage msg;

	while(m_sock->Poll(msg))
	{
		char buffer[BUFFER_SIZE];
		msg.Read(buffer,msg.Length());
		buffer[msg.Length()]=0;

		if(strcmp(buffer,"-check_for_server")==0)
		{
			strcpy(buffer,"-server_online");

			msg.Clear();
			msg.Write(buffer,strlen(buffer)+1);
			m_sock->SendTo(msg,m_sock->lastContact);
		}
	}
}
