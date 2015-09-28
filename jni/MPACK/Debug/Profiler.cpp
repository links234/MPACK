#include "Profiler.hpp"

#include "Time.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Time;

namespace MPACK
{
	namespace Profiler
	{
		const int SAMPLES = 30;

		int index;
		unordered_map<string, double> timeData[SAMPLES];
		double totalTime;
		stack<string> callStack;
		Timer *timer;

		vector< pair<string, double> > sortedData;

		void Init()
		{
			timer = Timer::Create();

			index = 0;
			for(int i=0;i<SAMPLES;++i)
			{
				timeData[i].clear();
			}

			totalTime = 0;
		}

		void Cleanup()
		{
			delete timer;
		}

		void Step()
		{
			unordered_map<string, double> temp;

			totalTime = 0.0;
			for(int i=0;i<SAMPLES;++i)
			{
				for(unordered_map<string, double>::iterator it=timeData[i].begin();it!=timeData[i].end();++it)
				{
					if(timeData[index].find(it->first)!=timeData[index].end())
					{
						temp[it->first]+=it->second/(double)(SAMPLES);
						totalTime+=it->second;
					}
				}
			}
			totalTime/=(double)(SAMPLES);

			sortedData.clear();
			for(unordered_map<string, double>::iterator it=temp.begin();it!=temp.end();++it)
			{
				sortedData.push_back( pair<string,double>(it->first, it->second) );
			}

			sort(sortedData.begin(),sortedData.end());

			++index;
			if(index == SAMPLES)
			{
				index = 0;
			}
			timeData[index].clear();
		}

		void Begin(std::string name)
		{
			float elapsedTime = timer->Time();
			if(!callStack.empty())
			{
				string prevCall = callStack.top();
				timeData[index][prevCall] += elapsedTime;
			}

			callStack.push(name);
			timer->Start();
		}

		void End()
		{
			float elapsedTime = timer->Time();
			string prevCall = callStack.top();
			timeData[index][prevCall] += elapsedTime;
			callStack.pop();
			timer->Start();
		}

		double GetTime(std::string name)
		{
			return timeData[index][name];
		}

		double GetPercent(std::string name)
		{
			return timeData[index][name]/totalTime*100;
		}

		vector< pair<string, double> >& GetTime()
		{
			return sortedData;
		}

		double GetTotalTime()
		{
			return totalTime;
		}
	}
}
