#ifndef MPACK_CRC32_HPP
#define MPACK_CRC32_HPP

#include "Types.hpp"

namespace MPACK
{
	class CRC32
	{
	public:
		CRC32();
		~CRC32();

		void Reset();
		void AddData(const char* pData, uint32 size);

		const uint32 Get();

	private:
		uint32 m_crc;
	};
}

#endif
