#ifndef MPACK_ANCHOR_HPP
#define MPACK_ANCHOR_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace UI
	{
		class Anchor
		{
		public:
			Anchor(double x=0.0, double y=0.0);

			double GetX() const;
			double GetY() const;

			Math::Vector2f GetPosition(const Math::AABB2Df &space) const;

			enum Type {Center,TopLeft,TopRight,BottomLeft,BottomRight,TopCenter,BottomCenter,LeftCenter,RightCenter};

			static Anchor Get(Type type);

		private:
			double m_x,m_y;
		};

		Math::Vector2f MatchAnchors(const Math::AABB2Df &targetSpace, const Anchor &targetAnchor, const Math::AABB2Df &objectSpace, const Anchor &objectAnchor, const Anchor &objectPosition);
	}
}

#endif
