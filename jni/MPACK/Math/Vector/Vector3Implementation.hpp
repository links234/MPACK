#ifndef MPACK_VECTOR3IMPLEMENTATION_HPP
#define MPACK_VECTOR3IMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline T Math::Vector3<T>::Length() const
	{
		return Math::Misc<T>::Sqrt(x*x+y*y+z*z);
	}

	template<class T> inline T Math::Vector3<T>::Magnitude() const
	{
		return Math::Misc<T>::Sqrt(x*x+y*y+z*z);
	}

	template<class T> inline T Math::Vector3<T>::Distance(const Math::Vector3<T> &point) const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		T dz=z-point.z;
		return Math::Misc<T>::Sqrt(dx*dx+dy*dy+dz*dz);
	}

	template<class T> inline T Math::Vector3<T>::Dot(const Math::Vector3<T> &v) const
	{
		return x*v.x+y*v.y+z*v.z;
	}

	template<class T> inline void Math::Vector3<T>::Normalize()
	{
		T d=Magnitude();
		if(d!=static_cast<T>(0))
		{
			x/=d;
			y/=d;
			z/=d;
		}
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::Normalized()
	{
		Math::Vector3<T> v(*this);
		v.Normalize();
		return v;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::Cross(const Math::Vector3<T> &v)const
	{
		Vector3<T> cp;
		cp.x=y*v.z-z*v.y;
		cp.y=z*v.x-x*v.z;
		cp.z=x*v.y-y*v.x;
		return cp;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator* (const Math::Matrix4<T> &m)const
	{
		Math::Vector3<T> B;
		T w =  x * m.m_matrix[0][3] + y * m.m_matrix[1][3] + z * m.m_matrix[2][3] + m.m_matrix[3][3];
		B.x = (x * m.m_matrix[0][0] + y * m.m_matrix[1][0] + z * m.m_matrix[2][0] + m.m_matrix[3][0]) / w;
		B.y = (x * m.m_matrix[0][1] + y * m.m_matrix[1][1] + z * m.m_matrix[2][1] + m.m_matrix[3][1]) / w;
		B.z = (x * m.m_matrix[0][2] + y * m.m_matrix[1][2] + z * m.m_matrix[2][2] + m.m_matrix[3][2]) / w;
		return B;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator* (const Math::Vector3<T> &v) const
	{
		return Math::Vector3<T>(x*v.x,y*v.y,z*v.z);
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator* (const T &s)const
	{
		return Math::Vector3<T>(x*s,y*s,z*s);
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator/ (const Math::Vector3<T> &v) const
	{
		Math::Vector3<T> t(*this);
		if(v.x==static_cast<T>(0))
		{
			t.x/=Misc<T>::c_Epsilon;
		}
		else
		{
			t.x/=v.x;
		}
		if(v.y==static_cast<T>(0))
		{
			t.y/=Misc<T>::c_Epsilon;
		}
		else
		{
			t.y/=v.y;
		}
		if(v.z==static_cast<T>(0))
		{
			t.z/=Misc<T>::c_Epsilon;
		}
		else
		{
			t.z/=v.z;
		}
		return t;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator/ (const T &s)const
	{
		if(s==static_cast<T>(0))
		{
			return Math::Vector3<T>(x/Math::Misc<T>::c_Epsilon,y/Math::Misc<T>::c_Epsilon,z/Math::Misc<T>::c_Epsilon);
		}
		return Math::Vector3<T>(x/s,y/s,z/s);
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator+ (const Math::Vector3<T> &v)const
	{
		return Math::Vector3<T>(x+v.x,y+v.y,z+v.z);
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator- (const Math::Vector3<T> &v)const
	{
		return Math::Vector3<T>(x-v.x,y-v.y,z-v.z);
	}

	template<class T> inline bool Math::Vector3<T>::operator!= (const Math::Vector3<T> &v)const
	{
		if(!Math::Misc<T>::Equal(x,v.x))
		{
			return true;
		}
		if(!Math::Misc<T>::Equal(y,v.y))
		{
			return true;
		}
		if(!Math::Misc<T>::Equal(z,v.z))
		{
			return true;
		}
		return false;
	}

	template<class T> inline bool Math::Vector3<T>::operator== (const Math::Vector3<T> &v)const
	{
		if(!Math::Misc<T>::Equal(x,v.x))
		{
			return false;
		}
		if(!Math::Misc<T>::Equal(y,v.y))
		{
			return false;
		}
		if(!Math::Misc<T>::Equal(z,v.z))
		{
			return false;
		}
		return true;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator+= (const Math::Vector3<T> &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator-= (const Math::Vector3<T> &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
		return *this;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator*=	(const Math::Matrix4<T> &m)
	{
		T w  =	x * m.m_matrix[0][3] + y * m.m_matrix[1][3] + z * m.m_matrix[2][3] + m.m_matrix[3][3];
		T tx =	(x * m.m_matrix[0][0] + y * m.m_matrix[1][0] + z * m.m_matrix[2][0] + m.m_matrix[3][0]) / w;
		T ty =	(x * m.m_matrix[0][1] + y * m.m_matrix[1][1] + z * m.m_matrix[2][1] + m.m_matrix[3][1]) / w;
		z	 =	(x * m.m_matrix[0][2] + y * m.m_matrix[1][2] + z * m.m_matrix[2][2] + m.m_matrix[3][2]) / w;
		x=tx;
		y=ty;
		return *this;
	}

	template<class T> inline Math::Vector3<T>	Math::Vector3<T>::operator*= (const Math::Vector3<T> &v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		return *this;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator*= (const T &s)
	{
		x*=s;
		y*=s;
		z*=s;
		return *this;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator/= (const Math::Vector3<T> &v)
	{
		if(v.x!=static_cast<T>(0))
		{
			x/=v.x;
		}
		else
		{
			x/=Math::Misc<T>::c_Epsilon;
		}
		if(v.y!=static_cast<T>(0))
		{
			y/=v.y;
		}
		else
		{
			y/=Math::Misc<T>::c_Epsilon;
		}
		if(v.z!=static_cast<T>(0))
		{
			z/=v.z;
		}
		else
		{
			z/=Math::Misc<T>::c_Epsilon;
		}
		return *this;
	}

	template<class T> inline Math::Vector3<T> Math::Vector3<T>::operator/= (const T &s)
	{
		x/=s;
		y/=s;
		z/=s;
		return *this;
	}
}

#endif
