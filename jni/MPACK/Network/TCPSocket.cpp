#include "TCPSocket.hpp"

#include "Debug.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Network
	{
		TCPSocket::TCPSocket()
			: isNonBlocking(false)
		{
			socket=Wrapper::Socket(Protocol::TCP);
		}

		TCPSocket::TCPSocket(int socket)
			: socket(socket), isNonBlocking(false)
		{
		}
	
		TCPSocket::~TCPSocket()
		{
			Shutdown();
		}

		void TCPSocket::Shutdown()
		{
			Wrapper::CloseSocket(socket);
		}

		int TCPSocket::SetNonBlocking(const bool &mode)
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

		bool TCPSocket::IsNonBlocking() const
		{
			return isNonBlocking;
		}
	}
}

