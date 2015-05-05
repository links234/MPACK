#include "UIHelper.hpp"

#include "Render.hpp"

using namespace MPACK::Math;
using namespace MPACK::Graphics;

namespace MPACK
{
	namespace UI
	{
		double Fit(const double &currentGlobalSize, const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*currentGlobalSize;
		}

		double FitWidth(const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*Render::GetScreenWidth();
		}

		double FitHeight(const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*Render::GetScreenHeight();
		}

		void FitByWidth(double &width, double &height, const double &originalWidth, const double &originalHeight)
		{
			double ratio=height/width;
			width=originalWidth;
			height=width*ratio;
		}

		void FitByHeight(double &width, double &height, const double &originalWidth, const double &originalHeight)
		{
			double ratio=width/height;
			height=originalHeight;
			width=height*ratio;
		}
	}
}
