#ifndef MPACK_UIWIDGET_HPP
#define MPACK_UIWIDGET_HPP

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
		class UIWidget
		{
		public:
			UIWidget();
			virtual ~UIWidget();

			virtual Math::AABB2Df GetUISpace() const = 0;
			virtual Anchor GetUIPositionAnchor() const = 0;
			virtual void UIWidgetCallback_SetPosition(const Math::Vector2f &position) = 0;
			virtual void UIWidgetCallback_SetX(const double &x) = 0;
			virtual void UIWidgetCallback_SetY(const double &y) = 0;
			virtual Math::Vector2f UIWidgetCallback_GetPosition() = 0;

			void UIMatch(const Anchor &object);
			void UIMatch(const Anchor &target, const Anchor &object);
			void UIMatchX(const Anchor &target, const Anchor &object);
			void UIMatchY(const Anchor &target, const Anchor &object);
		};
	}
}

#endif
