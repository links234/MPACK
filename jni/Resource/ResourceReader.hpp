#ifndef RESOURCEREADER_HPP
#define RESOURCEREADER_HPP

#include "Resource.hpp"

namespace Core
{
	class ResourceReader
	{
	public:
		ResourceReader(Resource *resource, int bufferSize=DefaultBufferSize);
		~ResourceReader();

		char Char();

		bool EndOfFile();

		static const int DefaultBufferSize;
	private:
		void NextChunk();

		Resource *m_resource;

		int m_bufferIndex;
		int m_bufferSize;
		int m_bytesLeft;
		int m_bytesLeftInBuffer;
		char *m_buffer;
	};
}

#endif
