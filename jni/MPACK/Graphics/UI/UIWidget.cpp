#include "UIWidget.hpp"

#include "Render.hpp"
#include "Anchor.hpp"

using namespace MPACK::Math;
using namespace MPACK::Graphics;

namespace MPACK
{
	namespace UI
	{
		UIWidget::UIWidget()
		{
		}

		UIWidget::~UIWidget()
		{
		}

		void UIWidget::UIMatch(const Anchor &object)
		{
			UIWidgetCallback_SetPosition(MatchAnchors(Render::GetUISpace(),ScreenToAnchor(UIWidgetCallback_GetPosition()),GetUISpace(),object,GetUIPositionAnchor()));
		}

		void UIWidget::UIMatch(const Anchor &target, const Anchor &object)
		{
			UIWidgetCallback_SetPosition(MatchAnchors(Render::GetUISpace(),target,GetUISpace(),object,GetUIPositionAnchor()));
		}

		void UIWidget::UIMatchX(const Anchor &target, const Anchor &object)
		{
			UIWidgetCallback_SetX(MatchAnchors(Render::GetUISpace(),target,GetUISpace(),object,GetUIPositionAnchor()).x);
		}

		void UIWidget::UIMatchY(const Anchor &target, const Anchor &object)
		{
			UIWidgetCallback_SetY(MatchAnchors(Render::GetUISpace(),target,GetUISpace(),object,GetUIPositionAnchor()).y);
		}
	}
}
