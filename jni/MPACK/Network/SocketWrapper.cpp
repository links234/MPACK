#include "SocketWrapper.hpp"

#include "Debug.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Network
	{
		namespace Wrapper
		{
			int Init()
			{
				LOGI("Network::Wrapper::Init() start");
#if defined(WINDOWS_PLATFORM)
				WORD versionRequested;
				WSADATA wsaData;
				DWORD bufferSize = 0;

				LPWSAPROTOCOL_INFO SelectedProtocol;
				int NumProtocols;

				versionRequested = MAKEWORD(2, 0);
				int error = WSAStartup(versionRequested, &wsaData);

				if(error)
				{
					LOGI("FATAL ERROR: WSAStartup failed (error = %d)", error);
					return 1;
				}
				else
				{
					LOGI("WSAStartup OK");

					if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
					{
						LOGI("FATAL ERROR: WinSock2 DLL does not support the correct version (%d.%d)",LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));

						WSACleanup();
						return 1;
					}
				}

				// Call WSAEnumProtocols to figure out how big of a buffer we need
				NumProtocols = WSAEnumProtocols(NULL, NULL, &bufferSize);

				if( (NumProtocols != SOCKET_ERROR) && (WSAGetLastError() != WSAENOBUFS) )
				{
					WSACleanup();
					return 1;
				}

				SelectedProtocol = (LPWSAPROTOCOL_INFO) new char[bufferSize];

				if(SelectedProtocol == NULL)
				{
					LOGI("FATAL ERROR: Failed to allocate memory for SelectedProtocol");
					WSACleanup();
					return 1;
				}

				int *protos = new int[2];

				protos[0] = IPPROTO_TCP;
				protos[1] = IPPROTO_UDP;

				NumProtocols = WSAEnumProtocols(protos, SelectedProtocol, &bufferSize);

				delete[] protos;
				protos = NULL;

				delete[] SelectedProtocol;
				SelectedProtocol = NULL;

				if(NumProtocols == SOCKET_ERROR)
				{
					LOGI("FATAL ERROR: Didn't find any required protocols");
					WSACleanup();
					return 1;
				}

#endif
				LOGI("Network::Wrapper::Init() successfully");
				return 0;
			}

			void Shutdown()
			{
#if defined(WINDOWS_PLATFORM)
				WSACleanup();
#endif
				LOGI("Network::Wrapper::Shutdown() successfully");
			}

			SOCKET Socket(Protocol::Protocol protocol)
			{
				int type;
				int proto;
				SOCKET sock;

				if(protocol == Protocol::TCP)
				{
					type = SOCK_STREAM;
					proto = IPPROTO_TCP;
				}
				else
				{
					type = SOCK_DGRAM;
					proto = IPPROTO_UDP;
				}

				if((sock = socket(AF_INET, type, proto)) == INVALID_SOCKET)
				{
					LOGI("Network::Socket() - socket() failed");

					LogLastError("socket()");
				}

				return sock;
			}

			int SetNonBlocking(const SOCKET sock, const u_long setMode)
			{
				u_long set = setMode;

#if	defined(WINDOWS_PLATFORM)
				return ioctlsocket(sock, FIONBIO, &set);
#elif	defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
				return ioctl(sock, FIONBIO, &set);
#endif
			}

			int SetBroadcast(const SOCKET sock, const u_long setMode)
			{
#if defined(WINDOWS_PLATFORM)
				char set = setMode;
				if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&set, sizeof(set))==SOCKET_ERROR)
#elif	defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
				u_long set = setMode;
				if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &set, sizeof(set))==SOCKET_ERROR)
#endif
				{
					LogLastError("setsockopt(SO_SOCKET, SO_BROADCAST)");
					return SOCKET_ERROR;
				}

				return 0;
			}

			int SetBroadcasting(SOCKET sock, int mode)
			{
				if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &mode, sizeof(int)) == SOCKET_ERROR)
				{
					LOGI("Network::SetBroadcasting failed");

					LogLastError("setsockopt()");

					return SOCKET_ERROR;
				}

				return 0;
			}

			void CloseSocket(SOCKET sock)
			{
#if	defined(WINDOWS_PLATFORM)
				closesocket(sock);
#elif	defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
				close(sock);
#endif
			}

			int GetPacket(SOCKET sock, char *data, int size, int flag, struct sockaddr *addr)
			{
				int ret;
				struct sockaddr tempFrom;
				socklen_t fromLen;

				fromLen = sizeof(tempFrom);

				ret = recvfrom(sock, data, size, flag, (struct sockaddr *) &tempFrom, &fromLen);

				if(addr != NULL)
				{
					*addr = tempFrom;
				}

				if(ret == -1)
				{
					return LogLastError_EWOULDBLOCK("recvfrom()");
				}

				return ret;
			}

			int SendPacket(SOCKET sock, const char *data, int size, int flag, const struct sockaddr *addr)
			{
				int ret;

				ret = sendto(sock, data, size, flag, addr, sizeof(sockaddr));

				if(ret == -1)
				{
					return LogLastError_EWOULDBLOCK("sendto()");
				}

				return ret;
			}

			bool Connect(SOCKET sock, const struct sockaddr *addr)
			{
				if(connect(sock, addr, sizeof(sockaddr)) == -1)
				{
					LogLastError("connect()");
					return false;
				}
				return true;
			}

			bool Listen(SOCKET sock, int queueSize)
			{
				if(listen(sock, queueSize) == SOCKET_ERROR)
				{
					LogLastError("listen()");
					return false;
				}
				return true;
			}

			int Accept(SOCKET sock, struct sockaddr *addr, socklen_t *addrLen)
			{
				int ret = accept(sock, addr, addrLen);
				if(ret == INVALID_SOCKET)
				{
					LogLastError_EWOULDBLOCK("accept()");
				}
				return ret;
			}

			int Receive(SOCKET sock, char *data, int size, int flag)
			{
				int ret;
				ret = recv(sock, data, size, flag);

				if(ret == -1)
				{
					return LogLastError_EWOULDBLOCK("recv()");
				}

				return ret;
			}

			int Send(SOCKET sock, const char *data, int size, int flag)
			{
				int ret;

				ret = send(sock, data, size, flag);

				if(ret == -1)
				{
					return LogLastError_EWOULDBLOCK("send()");
				}

				return ret;
			}

			void LogLastError(const char *message)
			{
#if defined(WINDOWS_PLATFORM)
				int errnumber = WSAGetLastError();
				LOGE("Error in %s : code %d : %s", message, errnumber, strerror(errno));
#elif	defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
				LOGE("Error in %s : code %d : %s", message, errno, strerror(errno));
#endif
			}

			int LogLastError_EWOULDBLOCK(const char *message)
			{
#if	defined(WINDOWS_PLATFORM)
				int errnumber = WSAGetLastError();
				if(errnumber == WSAEWOULDBLOCK)
				{
					return 0;
				}
				LOGE("Error in %s : code %d : %s", message, errnumber, strerror(errno));
#elif	defined(LINUX_PLATFORM) || defined(OSX_PLATFORM)
				if(errno == EWOULDBLOCK)
				{
					return 0;
				}
				LOGE("Error in %s : code %d : %s", message, errno, strerror(errno));
#endif
				return -1;
			}
		}
	}
}
