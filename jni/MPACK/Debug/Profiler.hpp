#ifndef MPACK_PROFILER_HPP
#define MPACK_PROFILER_HPP

#include "Types.hpp"
#include "DataCollecter.hpp"

namespace MPACK
{
	namespace Profiler
	{
		void Init();
		void Cleanup();

		void Step();

		void Begin(std::string name);
		void End();

		double GetTime(std::string name);
		double GetPercent(std::string name);

		std::vector< std::pair<std::string, double> >& GetTime();
		double GetTotalTime();
	}
}

#endif
