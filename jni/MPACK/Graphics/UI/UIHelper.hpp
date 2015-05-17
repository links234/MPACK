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
		double FitHeight(const double &originalSize, const double &originalGlobalSize);
		void FitByWidth(double &width, double &height, const double &originalWidth, const double &originalHeight);
		void FitByHeight(double &width, double &height, const double &originalWidth, const double &originalHeight);

		Anchor ScreenToAnchor(const MPACK::Math::Vector2f &position);
	}
}

#endif
