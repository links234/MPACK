#include "SocketAddress.hpp"

#define LAN_BROADCAST_ADDRESS	"255.255.255.255"
#define LOCALHOST_ADDRESS	"127.0.0.1"

namespace MPACK
{
	namespace Network
	{
		SocketAddress::SocketAddress()
		{
			memset(&addr,0,sizeof(sockaddr_in));
			addr.sin_family = AF_INET;
		}

		SocketAddress::SocketAddress(int port)
		{
			memset(&addr,0,sizeof(sockaddr_in));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = INADDR_ANY;
		}

		SocketAddress::SocketAddress(const char *IP, int port)
		{
			memset(&addr, 0, sizeof(sockaddr_in));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(IP);
		}

		SocketAddress::~SocketAddress()
		{
		}

		void SocketAddress::SetIP(const char *IP)
		{
			addr.sin_addr.s_addr = inet_addr(IP);
		}

		void SocketAddress::SetBroadcastAddress()
		{
			addr.sin_addr.s_addr = inet_addr(LAN_BROADCAST_ADDRESS);
		}

		void SocketAddress::SetLocalhostAddress()
		{
			addr.sin_addr.s_addr = inet_addr(LOCALHOST_ADDRESS);
		}

		void SocketAddress::SetAnyAddress()
		{
			addr.sin_addr.s_addr = INADDR_ANY;
		}

		void SocketAddress::SetPort(int port)
		{
			addr.sin_port = htons(port);
		}
	
		int SocketAddress::GetPort() const
		{
			return ntohs(addr.sin_port);
		}
	
		sockaddr* SocketAddress::GetAddrPointer() const
		{
			return (sockaddr*)&addr;
		}
	}
}

