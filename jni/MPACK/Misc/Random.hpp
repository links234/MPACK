#ifndef MPACK_RANDOM_HPP
#define MPACK_RANDOM_HPP

namespace MPACK
{
	namespace Core
	{
		namespace Random
		{
			void Init();

			int Int(int low, int high);

			double Double(double minv, double maxv);

			bool FlipCoin();
		}
	}
}

#endif
