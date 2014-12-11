#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSTIMESERVICE_HPP
#define MPACK_WINDOWSTIMESERVICE_HPP

#include "TimeService.hpp"

#include <windows.h>
#include <ctime>

namespace MPACK
{
	namespace Time
	{
		const ULONG MAX_SAMPLE_COUNT = 50;

		class WindowsTimeService : public TimeService
		{
		public:
			WindowsTimeService();

			void Reset();
			void Update();

			double Now();
			float 	Elapsed();

		private:
			bool		m_PerfHardware;
			float		m_TimeScale;
			float		m_TimeElapsed;
			float		m_TotalTime;
			__int64		m_CurrentTime;
			__int64		m_LastTime;
			__int64		m_PerfFreq;

			float		m_FrameTime[MAX_SAMPLE_COUNT];
			ULONG		m_SampleCount;

			unsigned long	m_FrameRate;
			unsigned long	m_FPSFrameCount;
			float			m_FPSTimeElapsed;
		};
	}
}
#endif

#endif
