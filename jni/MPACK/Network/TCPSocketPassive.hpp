#ifndef TCPSOCKETPASSIVE_HPP
#define TCPSOCKETPASSIVE_HPP

#include "TCPSocket.hpp"
#include "TCPSocketActive.hpp"

#include "SocketAddress.hpp"

namespace MPACK
{
	namespace Network
	{
		class TCPSocketPassive : public TCPSocket
		{
		public:
			TCPSocketPassive();
			~TCPSocketPassive();

			bool Listen(int port);
			bool Accept(TCPSocketActive **clientSock);
		};
	}
}

#endif

