#ifndef MPACK_SOCKETWRAPPER_HPP
#define MPACK_SOCKETWRAPPER_HPP

#ifdef WINDOWS_PLATFORM
	#pragma comment(lib,"Ws2_32.lib")

	#ifndef _WINSOCKAPI_
	#define _WINSOCKAPI_
	#endif
	#include <windows.h>
	#include <winsock2.h>
#elif defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
	#include <memory.h>
	#include <errno.h>
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#ifndef MSG_DONTWAIT
	#define MSG_DONTWAIT	0
#endif

#ifndef SOCKET_ERROR
	#define SOCKET_ERROR -1
#endif

#ifndef INVALID_SOCKET
	#define INVALID_SOCKET -1
#endif

#ifndef SOCKET
	#define SOCKET	int
#endif

#ifdef WINDOWS_PLATFORM
	typedef int socklen_t;
#endif

namespace MPACK
{
	namespace Network
	{
		namespace Protocol
		{
			enum Protocol
			{
				TCP,
				UDP
			};
		}

		namespace Wrapper
		{
			int Init();
			void Shutdown();

			SOCKET Socket(Protocol::Protocol protocol);
			int SetNonBlocking(const SOCKET sock, const u_long setMode);
			int SetBroadcast(const SOCKET sock, const u_long setMode);
			void CloseSocket(SOCKET sock);

			int GetPacket(SOCKET sock, char *data, int size, int flag, struct sockaddr *addr);
			int SendPacket(SOCKET sock, const char *data, int size, int flag, const struct sockaddr *addr);

			bool Connect(SOCKET sock, const struct sockaddr *addr);
			bool Listen(SOCKET sock, int queueSize);
			int Accept(SOCKET sock, struct sockaddr *addr, socklen_t *addrLen);

			int Receive(SOCKET sock, char *data, int size, int flag);
			int Send(SOCKET sock, const char *data, int size, int flag);

			void LogLastError(const char *message);
			int LogLastError_EWOULDBLOCK(const char *message);
		}
	}
}


#endif
