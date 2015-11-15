#include "UIHelper.hpp"

#include "Types.hpp"
#include "Render.hpp"
#include "Anchor.hpp"

using namespace std;
using namespace MPACK::Math;
using namespace MPACK::Graphics;

namespace MPACK
{
	namespace UI
	{
		double defaultOriginalWidth = 0.0;
		double defaultOriginalHeight = 0.0;

		double Fit(const double &currentGlobalSize, const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*currentGlobalSize;
		}

		double FitWidth(const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*Render::GetScreenWidth();
		}

		double FitWidth(const double &originalSize)
		{
			return FitWidth(originalSize, defaultOriginalWidth);
		}

		double FitHeight(const double &originalSize, const double &originalGlobalSize)
		{
			return originalSize/originalGlobalSize*Render::GetScreenHeight();
		}

		double FitHeight(const double &originalSize)
		{
			return FitHeight(originalSize, defaultOriginalHeight);
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

		void SetDefaultOriginalWidth(const double &width)
		{
			defaultOriginalWidth = width;
		}

		void SetDefaultOriginalHeight(const double &height)
		{
			defaultOriginalHeight = height;
		}

		double GetDefaultOriginalWidth()
		{
			return defaultOriginalWidth;
		}

		double GetDefaultOriginalHeight()
		{
			return defaultOriginalHeight;
		}

		double FitForMax(const double &originalSize)
		{
			return max(FitWidth(originalSize), FitHeight(originalSize));
		}

		double FitForMin(const double &originalSize)
		{
			return min(FitWidth(originalSize), FitHeight(originalSize));
		}

		Anchor ScreenToAnchor(const MPACK::Math::Vector2f &position)
		{
			return Anchor(position.x/Render::GetScreenWidth(),position.y/Render::GetScreenHeight());
		}
	}
}
