/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_TRANSFORMSTATE2_HPP
#define MPACK_TRANSFORMSTATE2_HPP

#include "Vector2.hpp"

namespace MPACK
{
	namespace Math
	{
		template<class T> class TransformState2
		{
		public:
			TransformState2(Vector2<T> translation = Vector2<T>(), T rotation = static_cast<T>(0), T scale = static_cast<T>(1)): m_translation(translation), m_rotation(rotation), m_scale(scale){}

			void 		Transform(Vector2<T> &vec2) const;
			Vector2<T> 	Transformed(Vector2<T> vec2) const;

			void 		SetTranslation(const Vector2<T> &translation);
			Vector2<T> 	GetTranslation() const;

			void 	SetRotation(const T &rotation);
			T		GetRotation() const;

			void 	SetScale(const T &scale);
			T		GetScale() const;

		private:
			Vector2<T> 	m_translation;
			T			m_rotation;
			T			m_scale;
		};
	}
}

#include "TransformState2Implementation.hpp"

#endif
