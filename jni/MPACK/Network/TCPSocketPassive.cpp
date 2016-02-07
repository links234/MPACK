#include "TCPSocketPassive.hpp"

#define TCP_LISTEN_CONNECTION_QUEUE_SIZE 8

namespace MPACK
{
	namespace Network
	{
		TCPSocketPassive::TCPSocketPassive()
		{
		}
		
		TCPSocketPassive::~TCPSocketPassive()
		{
		}

		bool TCPSocketPassive::Listen(int port)
		{
			inAddress.SetAnyAddress();
			inAddress.SetPort(port);
	
			if( bind(socket, inAddress.GetAddrPointer(), sizeof(sockaddr)) == SOCKET_ERROR)
			{
				return false;
			}

			if( !Wrapper::Listen(socket, TCP_LISTEN_CONNECTION_QUEUE_SIZE) )
			{
				return false;
			}
			return true;
		}

		bool TCPSocketPassive::Accept(TCPSocketActive **clientSock)
		{
			int ret = Wrapper::Accept(socket, NULL, NULL);
			if(ret == -1)
			{
				return false;
			}
			(*clientSock) = new TCPSocketActive(ret);
			return true;
		}
	}
}
