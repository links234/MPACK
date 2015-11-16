#include "ResourceReader.hpp"

#include "InputResource.hpp"

namespace MPACK
{
	namespace Core
	{
		const int ResourceReader::DefaultBufferSize = 64 * 1024;

		ResourceReader::ResourceReader(InputResource *resource, int bufferSize)
			: m_resource(resource), m_bufferIndex(0), m_bufferSize(bufferSize),
			  m_bytesLeft(resource->GetLength()), m_bytesLeftInBuffer(0)
		{
			m_buffer = new char[m_bufferSize];

			NextChunk();
		}

		ResourceReader::~ResourceReader()
		{
			delete[] m_buffer;
		}

		char ResourceReader::CharNext()
		{
			if(m_bytesLeftInBuffer <= 0)
			{
				NextChunk();
			}
			--m_bytesLeftInBuffer;
			return m_buffer[m_bufferIndex++];
		}

		char ResourceReader::Char()
		{
			return m_buffer[m_bufferIndex];
		}

		void ResourceReader::Next()
		{
			if(m_bytesLeftInBuffer <= 0)
			{
				NextChunk();
			}
			--m_bytesLeftInBuffer;
			++m_bufferIndex;
		}

		bool ResourceReader::EndOfFile()
		{
			return (m_bytesLeft == 0) && (m_bytesLeftInBuffer == 0);
		}

		void ResourceReader::NextChunk()
		{
			m_bufferIndex = 0;
			if(m_bytesLeft < m_bufferSize)
			{
				m_resource->Read(m_buffer, m_bytesLeft);

				m_bytesLeftInBuffer = m_bytesLeft;
				m_bytesLeft = 0;
			}
			else
			{
				m_resource->Read(m_buffer, m_bufferSize);

				m_bytesLeftInBuffer = m_bufferSize;
				m_bytesLeft -= m_bytesLeftInBuffer;
			}
		}
	}
}
