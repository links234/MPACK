#ifndef SOCKETADDRESS_HPP
#define SOCKETADDRESS_HPP

#include "SocketWrapper.hpp"

namespace MPACK
{
	namespace Network
	{
		class SocketAddress
		{
		public:
			SocketAddress();
			SocketAddress(int port);
			SocketAddress(const char *IP, int port);
			~SocketAddress();

			void SetIP(const char *IP);
			void SetBroadcastAddress();
			void SetLocalhostAddress();
			void SetAnyAddress();
			void SetPort(int port);

			int GetPort() const;
			sockaddr* GetAddrPointer() const;

		private:
			sockaddr_in	addr;
		};
	}
}

#endif

