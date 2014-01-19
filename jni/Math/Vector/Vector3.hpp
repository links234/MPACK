/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace Math
{
	template<class T> class Matrix4;

	template<class T> class Vector3
	{
	public:
		Vector3(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0)): x(x), y(y), z(z){};

		T Length() const;
		T Magnitude() const;
		T Distance(const Vector3<T> &point) const;
		T Dot(const Vector3<T> &v) const;
		void		Normalize();
		Vector3<T>	Normalized();
		Vector3<T>	Cross		(const Vector3<T> &v) const;
		Vector3<T>	operator*	(const Matrix4<T> &m) const;
		Vector3<T>	operator*	(const Vector3<T> &v) const;
		Vector3<T>	operator*	(const T &s) const;
		Vector3<T>	operator/	(const Vector3<T> &v) const;
		Vector3<T>	operator/	(const T &s) const;
		Vector3<T>	operator+	(const Vector3<T> &v) const;
		Vector3<T>	operator-	(const Vector3<T> &v) const;
		bool		operator!=	(const Vector3<T> &v) const;
		bool		operator==	(const Vector3<T> &v) const;
		Vector3<T>	operator+=	(const Vector3<T> &v);
		Vector3<T>	operator-=	(const Vector3<T> &v);
		Vector3<T>	operator*=	(const Matrix4<T> &m);
		Vector3<T>	operator*=	(const Vector3<T> &v);
		Vector3<T>	operator*=	(const T &s);
		Vector3<T>	operator/=	(const Vector3<T> &v);
		Vector3<T>	operator/=	(const T &s);

		T x;
		T y;
		T z;
	};

	template<class T> inline T Vector3<T>::Length() const
	{
		return Misc<T>::Sqrt(x*x+y*y+z*z);
	}

	template<class T> inline T Vector3<T>::Magnitude() const
	{
		return Misc<T>::Sqrt(x*x+y*y+z*z);
	}

	template<class T> inline T Vector3<T>::Distance(const Vector3<T> &point) const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		T dz=z-point.z;
		return Misc<T>::Sqrt(dx*dx+dy*dy+dz*dz);
	}

	template<class T> inline T Vector3<T>::Dot(const Vector3<T> &v) const
	{
		return x*v.x+y*v.y+z*v.z;
	}

	template<class T> inline void Vector3<T>::Normalize()
	{
		T d=Magnitude();
		if(d!=static_cast<T>(0))
		{
			x/=d;
			y/=d;
			z/=d;
		}
	}

	template<class T> inline Vector3<T> Vector3<T>::Normalized()
	{
		Vector3<T> v(*this);
		v.Normalize();
		return v;
	}

	template<class T> inline Vector3<T> Vector3<T>::Cross(const Vector3<T> &v)const
	{
		Vector3<T> cp;
		cp.x=y*v.z-z*v.y;
		cp.y=z*v.x-x*v.z;
		cp.z=x*v.y-y*v.x;
		return cp;
	}

	template<class T> inline Vector3<T> Vector3<T>::operator* (const Matrix4<T> &m)const
	{
		Vector3<T> B;
		T w =  x * m.m_matrix[0][3] + y * m.m_matrix[1][3] + z * m.m_matrix[2][3] + m.m_matrix[3][3];
		B.x = (x * m.m_matrix[0][0] + y * m.m_matrix[1][0] + z * m.m_matrix[2][0] + m.m_matrix[3][0]) / w;
		B.y = (x * m.m_matrix[0][1] + y * m.m_matrix[1][1] + z * m.m_matrix[2][1] + m.m_matrix[3][1]) / w;
		B.z = (x * m.m_matrix[0][2] + y * m.m_matrix[1][2] + z * m.m_matrix[2][2] + m.m_matrix[3][2]) / w;
		return B;
	}

	template<class T> inline Vector3<T>	Vector3<T>::operator* (const Vector3<T> &v) const
	{
		return Vector3<T>(x*v.x,y*v.y,z*v.z);
	}

	template<class T> inline Vector3<T> Vector3<T>::operator* (const T &s)const
	{
		return Vector3<T>(x*s,y*s,z*s);
	}

	template<class T> inline Vector3<T>	Vector3<T>::operator/	(const Vector3<T> &v) const
	{
		Vector3<T> t(*this);
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

	template<class T> inline Vector3<T> Vector3<T>::operator/  (const T &s)const
	{
		if(s==static_cast<T>(0))
		{
			return Vector3<T>(x/Misc<T>::c_Epsilon,y/Misc<T>::c_Epsilon,z/Misc<T>::c_Epsilon);
		}
		return Vector3<T>(x/s,y/s,z/s);
	}

	template<class T> inline Vector3<T> Vector3<T>::operator+ (const Vector3<T> &v)const
	{
		return Vector3<T>(x+v.x,y+v.y,z+v.z);
	}

	template<class T> inline Vector3<T> Vector3<T>::operator- (const Vector3<T> &v)const
	{
		return Vector3<T>(x-v.x,y-v.y,z-v.z);
	}

	template<class T> inline bool	Vector3<T>::operator!= (const Vector3<T> &v)const
	{
		if(!Misc<T>::Equal(x,v.x))
		{
			return true;
		}
		if(!Misc<T>::Equal(y,v.y))
		{
			return true;
		}
		if(!Misc<T>::Equal(z,v.z))
		{
			return true;
		}
		return false;
	}

	template<class T> inline bool	Vector3<T>::operator== (const Vector3<T> &v)const
	{
		if(!Misc<T>::Equal(x,v.x))
		{
			return false;
		}
		if(!Misc<T>::Equal(y,v.y))
		{
			return false;
		}
		if(!Misc<T>::Equal(z,v.z))
		{
			return false;
		}
		return true;
	}

	template<class T> inline Vector3<T> Vector3<T>::operator+= (const Vector3<T> &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}

	template<class T> inline Vector3<T> Vector3<T>::operator-= (const Vector3<T> &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
		return *this;
	}

	template<class T> inline Vector3<T>	Vector3<T>::operator*=	(const Matrix4<T> &m)
	{
		T w  =	x * m.m_matrix[0][3] + y * m.m_matrix[1][3] + z * m.m_matrix[2][3] + m.m_matrix[3][3];
		T tx =	(x * m.m_matrix[0][0] + y * m.m_matrix[1][0] + z * m.m_matrix[2][0] + m.m_matrix[3][0]) / w;
		T ty =	(x * m.m_matrix[0][1] + y * m.m_matrix[1][1] + z * m.m_matrix[2][1] + m.m_matrix[3][1]) / w;
		z	 =	(x * m.m_matrix[0][2] + y * m.m_matrix[1][2] + z * m.m_matrix[2][2] + m.m_matrix[3][2]) / w;
		x=tx;
		y=ty;
		return *this;
	}

	template<class T> inline Vector3<T>	Vector3<T>::operator*=	(const Vector3<T> &v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		return *this;
	}

	template<class T> inline Vector3<T> Vector3<T>::operator*= (const T &s)
	{
		x*=s;
		y*=s;
		z*=s;
		return *this;
	}

	template<class T> inline Vector3<T>	Vector3<T>::operator/=	(const Vector3<T> &v)
	{
		if(v.x!=static_cast<T>(0))
		{
			x/=v.x;
		}
		else
		{
			x/=Misc<T>::c_Epsilon;
		}
		if(v.y!=static_cast<T>(0))
		{
			y/=v.y;
		}
		else
		{
			y/=Misc<T>::c_Epsilon;
		}
		if(v.z!=static_cast<T>(0))
		{
			z/=v.z;
		}
		else
		{
			z/=Misc<T>::c_Epsilon;
		}
		return *this;
	}

	template<class T> inline Vector3<T> Vector3<T>::operator/= (const T &s)
	{
		x/=s;
		y/=s;
		z/=s;
		return *this;
	}
}

#endif
