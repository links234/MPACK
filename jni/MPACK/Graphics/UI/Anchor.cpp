#include "Anchor.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace UI
	{
		Anchor::Anchor(double x, double y)
			: m_x(x), m_y(y)
		{
		}

		double Anchor::GetX() const
		{
			return m_x;
		}

		double Anchor::GetY() const
		{
			return m_y;
		}

		Vector2f Anchor::GetPosition(const AABB2Df &space) const
		{
			return Vector2f(Misc<float>::Interpolate(space.m_xmin,space.m_xmax,m_x),Misc<float>::Interpolate(space.m_ymin,space.m_ymax,m_y));
		}

		enum AnchorType {Center,TopLeft,TopRight,BottomLeft,BottomRight,TopCenter,BottomCenter,LeftCenter,RightCenter};

		Anchor Anchor::Get(Type type)
		{
			switch(type)
			{
				case TopLeft:
					return Anchor(0.0,0.0);
				case TopRight:
					return Anchor(1.0,0.0);
				case BottomLeft:
					return Anchor(0.0,1.0);
				case BottomRight:
					return Anchor(1.0,1.0);
				case TopCenter:
					return Anchor(0.5,0.0);
				case BottomCenter:
					return Anchor(0.5,1.0);
				case LeftCenter:
					return Anchor(0.0,0.5);
				case RightCenter:
					return Anchor(1.0,0.5);
				case Center:
				default:
					return Anchor(0.5,0.5);
			}
		}

		Vector2f MatchAnchors(const AABB2Df &targetSpace, const Anchor &targetAnchor, const AABB2Df &objectSpace, const Anchor &objectAnchor, const Anchor &objectPosition)
		{
			Vector2f targetAnchorPos=targetAnchor.GetPosition(targetSpace);
			Vector2f objectAnchorPos=objectAnchor.GetPosition(objectSpace);
			Vector2f objectPos=objectPosition.GetPosition(objectSpace);
			return targetAnchorPos+objectPos-objectAnchorPos;
		}
	}
}
