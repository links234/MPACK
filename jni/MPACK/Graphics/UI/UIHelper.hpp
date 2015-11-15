#ifndef MPACK_UIHELPER_HPP
#define MPACK_UIHELPER_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace UI
	{
		class Anchor;
	}
}

namespace MPACK
{
	namespace UI
	{
		double Fit(const double &currentGlobalSize, const double &originalSize, const double &originalGlobalSize);
		double FitWidth(const double &originalSize, const double &originalGlobalSize);
		double FitWidth(const double &originalSize);
		double FitHeight(const double &originalSize, const double &originalGlobalSize);
		double FitHeight(const double &originalSize);
		void FitByWidth(double &width, double &height, const double &originalWidth, const double &originalHeight);
		void FitByHeight(double &width, double &height, const double &originalWidth, const double &originalHeight);

		void SetDefaultOriginalWidth(const double &width);
		void SetDefaultOriginalHeight(const double &height);
		double GetDefaultOriginalWidth();
		double GetDefaultOriginalHeight();

		double FitForMax(const double &originalSize);
		double FitForMin(const double &originalSize);

		Anchor ScreenToAnchor(const MPACK::Math::Vector2f &position);
	}
}

#endif
