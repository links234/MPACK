#ifndef MPACK_TRANSFORMSTATE2IMPLEMENTATION_HPP
#define MPACK_TRANSFORMSTATE2IMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline void Math::TransformState2<T>::Transform(Math::Vector2<T> &vec2) const
	{
		vec2.Rotate(m_rotation);
		vec2*=m_scale;
		vec2+=m_translation;
	}

	template<class T> inline Math::Vector2<T> Math::TransformState2<T>::Transformed(Math::Vector2<T> vec2) const
	{
		vec2.Rotate(m_rotation);
		vec2*=m_scale;
		vec2+=m_translation;
		return vec2;
	}

	template<class T> inline void Math::TransformState2<T>::SetTranslation(const Math::Vector2<T> &translation)
	{
		m_translation=translation;
	}

	template<class T> inline Math::Vector2<T> Math::TransformState2<T>::GetTranslation() const
	{
		return m_translation;
	}

	template<class T> inline void Math::TransformState2<T>::SetRotation(const T &rotation)
	{
		m_rotation=rotation;
	}

	template<class T> inline T Math::TransformState2<T>::GetRotation() const
	{
		return m_rotation;
	}

	template<class T> inline void Math::TransformState2<T>::SetScale(const T &scale)
	{
		m_scale=scale;
	}

	template<class T> inline T Math::TransformState2<T>::GetScale() const
	{
		return m_rotation;
	}
}

#endif
