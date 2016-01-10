#ifndef UDPMESSAGE_HPP
#define UDPMESSAGE_HPP

#define UDPMSG_MAXBUFFERSIZE	1024

namespace MPACK
{
	namespace Network
	{
		class UDPSocket;
		class TCPSocketActive;

		class UDPMessage
		{
		friend class UDPSocket;
		friend class TCPSocketActive;
		public:
			UDPMessage();
			~UDPMessage();

			void Clear();
			void Seek(int count);

			bool Write(char *src, int count);
			bool Read(char *dest, int count);

			int Length() const;

		private:
			char data[UDPMSG_MAXBUFFERSIZE];
			int length;
			int pointer;
		};
	}
}

#endif

