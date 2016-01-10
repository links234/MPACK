#ifndef MPACK_TCPSOCKET_HPP
#define MPACK_TCPSOCKET_HPP

#include "SocketWrapper.hpp"
#include "SocketAddress.hpp"

namespace MPACK
{
	namespace Network
	{
		class TCPSocket
		{
		public:
			void Shutdown(void);

			int SetNonBlocking(const bool &mode);
			bool IsNonBlocking() const;

		protected:
			TCPSocket();
			TCPSocket(int socket);
			~TCPSocket();
		
			SocketAddress inAddress;
			SOCKET socket;
			bool isNonBlocking;
		};
	}
}

#endif
