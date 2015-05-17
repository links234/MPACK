#include "Random.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

namespace MPACK
{
	namespace Core
	{
		namespace Random
		{
			void Init()
			{
				srand((int)time(NULL));
			}

			int Int(int low, int high)
			{
				int gap(0);
				if(low>high)
				{
					gap=low;
					low=high;
					high=gap;
					gap=0;
				}
				if(low<0)
				{
					gap=-low;
					low=0;
					high+=gap;
				}
				return low+(rand()%(high-low+1))-gap;
			}

			double Double(double low, double high)
			{
				double temp;

				if (low > high)
				{
					temp = low;
					low = high;
					high = temp;
				}

				temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0))* (high - low) + low;
				return temp;
			}

			bool FlipCoin()
			{
				return rand()&1;
			}
		}
	}
}
