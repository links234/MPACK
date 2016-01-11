#ifndef MPACK_UDPMESSAGE_HPP
#define MPACK_UDPMESSAGE_HPP

#define UDPMSG_MAXBUFFERSIZE	1024

namespace MPACK
{
	namespace Network
	{
		class UDPSocket;
		class TCPSocketActive;

		class UDPMessage
		{
		public:
			UDPMessage();
			~UDPMessage();

			void Clear();
			void Seek(int count);

			bool Write(const char *src, int count);
			bool Read(char *dest, int count);

			int Length() const;

		private:
			char data[UDPMSG_MAXBUFFERSIZE];
			int length;
			int pointer;

			friend class UDPSocket;
			friend class TCPSocketActive;
		};
	}
}

#endif

