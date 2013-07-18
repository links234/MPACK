/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef TRANSFORMSTATE2_HPP
#define TRANSFORMSTATE2_HPP

#include "Vector2.hpp"

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

	template<class T> inline void TransformState2<T>::Transform(Vector2<T> &vec2) const
	{
		vec2.Rotate(m_rotation);
		vec2*=m_scale;
		vec2+=m_translation;
	}

	template<class T> inline Vector2<T> TransformState2<T>::Transformed(Vector2<T> vec2) const
	{
		vec2.Rotate(m_rotation);
		vec2*=m_scale;
		vec2+=m_translation;
		return vec2;
	}

	template<class T> inline void TransformState2<T>::SetTranslation(const Vector2<T> &translation)
	{
		m_translation=translation;
	}

	template<class T> inline Vector2<T> TransformState2<T>::GetTranslation() const
	{
		return m_translation;
	}

	template<class T> inline void TransformState2<T>::SetRotation(const T &rotation)
	{
		m_rotation=rotation;
	}

	template<class T> inline T TransformState2<T>::GetRotation() const
	{
		return m_rotation;
	}

	template<class T> inline void TransformState2<T>::SetScale(const T &scale)
	{
		m_scale=scale;
	}

	template<class T> inline T TransformState2<T>::GetScale() const
	{
		return m_rotation;
	}
}

#endif
