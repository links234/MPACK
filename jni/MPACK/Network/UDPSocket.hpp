#ifndef MPACK_UDPSOCKET_HPP
#define MPACK_UDPSOCKET_HPP

#include "SocketWrapper.hpp"
#include "SocketAddress.hpp"
#include "UDPMessage.hpp"

namespace MPACK
{
	namespace Network
	{
		class UDPSocket
		{
		public:
			UDPSocket();
			~UDPSocket();

			bool Bind(int port);
			void Shutdown(void);

			int SetNonBlocking(const bool &mode);
			int SetBroadcast(const bool &mode);

			bool IsNonBlocking() const;
			bool IsBroadcasting() const;

			void EnableCRC32();
			void DisableCRC32();
			bool IsCRC32Enabled() const;

			bool Poll(UDPMessage &message);
			int SendTo(UDPMessage &message, const SocketAddress &address);

			SocketAddress inAddress, lastContact;

		private:
			SOCKET socket;
			bool isNonBlocking;
			bool isBroadcasting;
			bool isCRC32Enabled;
		};
	}
}

#endif
