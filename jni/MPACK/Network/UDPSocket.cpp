#include "UDPSocket.hpp"

#include "Debug.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Network
	{
		UDPSocket::UDPSocket()
			: isNonBlocking(false), isBroadcasting(false)
		{
			socket=Wrapper::Socket(Protocol::UDP);
		}

		UDPSocket::~UDPSocket()
		{
			Shutdown();
		}

		bool UDPSocket::Bind(int port)
		{
			inAddress.SetAnyAddress();
			inAddress.SetPort(port);

			if(bind(socket, inAddress.GetAddrPointer(), sizeof(sockaddr)) == 0)
			{
				return true;
			}
			return false;
		}

		void UDPSocket::Shutdown()
		{
			Wrapper::CloseSocket(socket);
		}

		int UDPSocket::SetNonBlocking(const bool &mode)
		{
			if(mode==isNonBlocking)
			{
				return 0;
			}
			isNonBlocking = mode;

			u_long set = 1;
			if(!isNonBlocking)
			{
				set = 0;
			}

#ifdef WINDOWS_PLATFORM
			return ioctlsocket(socket, FIONBIO, &set);
#elif	defined(LINUX_PLATFORM)
			return 0;//ioctl(sock, FIONBIO, &set);
#endif
		}

		int UDPSocket::SetBroadcast(const bool &mode)
		{
			if(mode==isBroadcasting)
			{
				return 0;
			}
			isBroadcasting=mode;

			u_long set = 0;
			if(isBroadcasting)
			{
				set = 1;
			}

			return Wrapper::SetBroadcast(socket,set);
		}

		bool UDPSocket::IsNonBlocking() const
		{
			return isNonBlocking;
		}

		bool UDPSocket::IsBroadcasting() const
		{
			return isBroadcasting;
		}

		bool UDPSocket::Poll(UDPMessage &message)
		{
			int flag=0;
			if(isNonBlocking)
			{
				flag=MSG_DONTWAIT;
			}

			message.Clear();
			int ret=Wrapper::GetPacket(socket, message.data, UDPMSG_MAXBUFFERSIZE, flag, lastContact.GetAddrPointer());
			if(ret>0)
			{
				message.length=ret;
				return true;
			}
			return false;
		}

		int UDPSocket::SendTo(const UDPMessage &message, const SocketAddress &address)
		{
			int flag=0;
			if(isNonBlocking)
			{
				flag=MSG_DONTWAIT;
			}

			return Wrapper::SendPacket(socket, message.data, message.length, flag, (const sockaddr*)address.GetAddrPointer());
		}
	}
}
