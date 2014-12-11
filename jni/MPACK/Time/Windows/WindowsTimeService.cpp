#ifdef WINDOWS_PLATFORM

#include "WindowsTimeService.hpp"

#include "Log.hpp"

#include <time.h>
#include <cstdlib>
#include <cmath>

namespace MPACK
{
	namespace Time
	{
		WindowsTimeService::WindowsTimeService()
		{
			if (QueryPerformanceFrequency((LARGE_INTEGER *)&m_PerfFreq))
			{
				m_PerfHardware		= TRUE;
				QueryPerformanceCounter((LARGE_INTEGER *) &m_LastTime);
				m_TimeScale			= 1.0f / m_PerfFreq;
			}
			else
			{
				m_PerfHardware		= FALSE;
				m_LastTime			= timeGetTime();
				m_TimeScale			= 0.001f;
			}

			Reset();
		}

		void WindowsTimeService::Reset()
		{
			m_SampleCount       = 0;
			m_FrameRate			= 0;
			m_FPSFrameCount		= 0;
			m_FPSTimeElapsed	= 0.0f;
			m_TimeElapsed		= 0.0f;
			m_TotalTime			= 0.0f;
		}

		void WindowsTimeService::Update()
		{
			float fTimeElapsed;

			if ( m_PerfHardware )
			{
				QueryPerformanceCounter((LARGE_INTEGER *)&m_CurrentTime);
			}
			else
			{
				m_CurrentTime = timeGetTime();
			}

			fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

			m_LastTime = m_CurrentTime;

			if ( fabsf(fTimeElapsed - m_TimeElapsed) < 1.0f  )
			{
				memmove( &m_FrameTime[1], m_FrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float) );
				m_FrameTime[ 0 ] = fTimeElapsed;
				if ( m_SampleCount < MAX_SAMPLE_COUNT ) m_SampleCount++;
			}

			m_FPSFrameCount++;
			m_FPSTimeElapsed += m_TimeElapsed;
			if ( m_FPSTimeElapsed > 1.0f)
			{
				m_FrameRate			= m_FPSFrameCount;
				m_FPSFrameCount		= 0;
				m_FPSTimeElapsed	= 0.0f;
			}

			m_TimeElapsed = 0.0f;
			for ( ULONG i = 0; i < m_SampleCount; i++ ) m_TimeElapsed += m_FrameTime[ i ];
			if ( m_SampleCount > 0 ) m_TimeElapsed /= m_SampleCount;

			m_TotalTime+=m_TimeElapsed;
		}

		double WindowsTimeService::Now()
		{
			return m_TotalTime;
		}

		float WindowsTimeService::Elapsed()
		{
			return m_TimeElapsed;
		}
	}
}

#endif

