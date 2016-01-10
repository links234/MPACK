#include "UDPMessage.hpp"

#include <cstring>

#include "Debug.hpp"

namespace MPACK
{
	namespace Network
	{
		UDPMessage::UDPMessage()
			: length(0), pointer(0)
		{
			memset(data,0,UDPMSG_MAXBUFFERSIZE);
		}

		UDPMessage::~UDPMessage()
		{
		}

		void UDPMessage::Clear()
		{
			length=0;
			pointer=0;
		}

		bool UDPMessage::Write(char *src, int count)
		{
			if(count+length>UDPMSG_MAXBUFFERSIZE)
			{
				LOGW("UDPMessage::Write message length exceed UDPMSG_MAXBUFFERSIZE");
				return false;
			}
			memcpy(data+length,src,count);
			length+=count;
			return true;
		}

		void UDPMessage::Seek(int count)
		{
			pointer=count;
		}

		bool UDPMessage::Read(char *dest, int count)
		{
			if(count+pointer>length)
			{
				LOGW("UDPMessage::Read requested data exceed message length");
				return false;
			}
			memcpy(dest,data+pointer,count);
			pointer+=count;
			return true;
		}

		int UDPMessage::Length() const
		{
			return length;
		}
	}
}
