#include "TCPSocketActive.hpp"

namespace MPACK
{
	namespace Network
	{
		TCPSocketActive::TCPSocketActive()
		{
		}
	

		TCPSocketActive::TCPSocketActive(int socket)
			: TCPSocket(socket)
		{
		}

		TCPSocketActive::~TCPSocketActive()
		{
		}

		bool TCPSocketActive::Connect(const SocketAddress &addr)
		{
			if(!Wrapper::Connect(socket, (const struct sockaddr*)(&addr)))
			{
				return false;
			}
			return true;
		}

		int TCPSocketActive::Send(const UDPMessage &message)
		{
			int flag=0;
			if(isNonBlocking)
			{
				flag=MSG_DONTWAIT;
			}
	
			return Wrapper::Send(socket, message.data, message.length, flag);
		}

		bool TCPSocketActive::Receive(UDPMessage &message)
		{
			int flag=0;
			if(isNonBlocking)
			{
				flag=MSG_DONTWAIT;
			}

			message.Clear();
			int ret=Wrapper::Receive(socket, message.data, UDPMSG_MAXBUFFERSIZE, flag);
			if(ret>=0)
			{
				message.length=ret;
				return true;
			}
			return false;
		}
	}
}
