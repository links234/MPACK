#ifndef MPACK_TCPSOCKETACTIVE_HPP
#define MPACK_TCPSOCKETACTIVE_HPP

#include "TCPSocket.hpp"
#include "UDPMessage.hpp"
#include "SocketAddress.hpp"

namespace MPACK
{
	namespace Network
	{
		class TCPSocketActive : public TCPSocket
		{
		public:
			TCPSocketActive();
			TCPSocketActive(int socket);
			~TCPSocketActive();

			bool Connect(const SocketAddress &addr);
			int Send(const UDPMessage &message);
			bool Receive(UDPMessage &message);
		};
	}
}

#endif

