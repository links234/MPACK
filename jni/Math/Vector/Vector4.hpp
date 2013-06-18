/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace Math
{
	template<class T> class Vector4
	{
	public:
		Vector4<T>(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0), T w = static_cast<T>(0)): x(x), y(y), z(z), w(w){};

		T Length() const;
		T Magnitude() const;
		T Distance(const Vector4<T> &point) const;
		T Dot(const Vector4<T> &v) const;
		void Normalize();
		Vector4<T>	Normalized();
		Vector4<T>	operator*	(const Vector4<T> &v) const;
		Vector4<T>	operator*	(const T &s) const;
		Vector4<T>	operator/	(const Vector4<T> &v) const;
		Vector4<T>	operator/	(const T &s) const;
		Vector4<T>	operator+	(const Vector4<T> &v) const;
		Vector4<T>	operator-	(const Vector4<T> &v) const;
		bool		operator!=	(const Vector4<T> &v) const;
		bool		operator==	(const Vector4<T> &v) const;
		Vector4<T>	operator+=	(const Vector4<T> &v);
		Vector4<T>	operator-=	(const Vector4<T> &v);
		Vector4<T>	operator*=	(const Vector4<T> &v);
		Vector4<T>	operator*=	(const T &s);
		Vector4<T>	operator/=	(const Vector4<T> &v);
		Vector4<T>	operator/=	(const T &s);

		T x;
		T y;
		T z;
		T w;
	};

	template<class T> inline T Vector4<T>::Length() const
	{
		return Misc<T>::Sqrt(x*x+y*y+z*z+w*w);
	}

	template<class T> inline T Vector4<T>::Magnitude() const
	{
		return Misc<T>::Sqrt(x*x+y*y+z*z+w*w);
	}

	template<class T> inline T Vector4<T>::Distance(const Vector4<T> &point)const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		T dz=z-point.z;
		T dw=w-point.w;
		return Misc<T>::Sqrt(dx*dx+dy*dy+dz*dz+dw*dw);
	}

	template<class T> inline T Vector4<T>::Dot(const Vector4<T> &v) const
	{
		return x*v.x+y*v.y+z*v.z+w*v.w;
	}

	template<class T> inline void Vector4<T>::Normalize()
	{
		T d=Magnitude();
		if(d!=static_cast<T>(0))
		{
			x/=d;
			y/=d;
			z/=d;
			w/=d;
		}
	}

	template<class T> inline Vector4<T> Vector4<T>::Normalized()
	{
		Vector4<T> v(*this);
		v.normalize();
		return v;
	}

	template<class T> inline Vector4<T>	Vector4<T>::operator*	(const Vector4<T> &v) const
	{
		return Vector4<T>(v.x*x,v.y*y,v.z*z,v.w*w);
	}

	template<class T> inline Vector4<T> Vector4<T>::operator*  (const T &s) const
	{
		return Vector4<T>(x*s,y*s,z*s,w*s);
	}

	template<class T> inline Vector4<T>	Vector4<T>::operator/	(const Vector4<T> &v) const
	{
		Vector4<T> t;
		if(v.x==static_cast<T>(0))
		{
			t.x=x/Misc<T>::c_Epsilon;
		}
		else
		{
			t.x=x/v.x;
		}
		if(v.y==static_cast<T>(0))
		{
			t.y=y/Misc<T>::c_Epsilon;
		}
		else
		{
			t.y=y/v.y;
		}
		if(v.z==static_cast<T>(0))
		{
			t.z=z/Misc<T>::c_Epsilon;
		}
		else
		{
			t.z=z/v.z;
		}
		if(v.w==static_cast<T>(0))
		{
			t.w=w/Misc<T>::c_Epsilon;
		}
		else
		{
			t.w=w/v.w;
		}
		return t;
	}

	template<class T> inline Vector4<T> Vector4<T>::operator/  (const T &s) const
	{
		if(s==static_cast<T>(0))
		{
			return Vector4<T>(x/Misc<T>::c_Epsilon,y/Misc<T>::c_Epsilon,z/Misc<T>::c_Epsilon,w/Misc<T>::c_Epsilon);
		}
		return Vector4<T>(x/s,y/s,z/s,w/s);
	}

	template<class T> inline Vector4<T> Vector4<T>::operator+  (const Vector4<T> &v) const
	{
		return Vector4<T>(x+v.x,y+v.y,z+v.z,w+v.w);
	}

	template<class T> inline Vector4<T> Vector4<T>::operator-  (const Vector4<T> &v) const
	{
		return Vector4<T>(x-v.x,y-v.y,z-v.z,w-v.w);
	}

	template<class T> inline bool Vector4<T>::operator!= (const Vector4<T> &v)const
	{
		if(Misc<T>::Equal(x,v.x))
		{
			return false;
		}
		if(Misc<T>::Equal(y,v.y))
		{
			return false;
		}
		if(Misc<T>::Equal(z,v.z))
		{
			return false;
		}
		if(Misc<T>::Equal(w,v.w))
		{
			return false;
		}
		return true;
	}

	template<class T> inline bool Vector4<T>::operator==(const Vector4<T> &v) const
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
		if(!Misc<T>::Equal(w,v.w))
		{
			return false;
		}
		return true;
	}

	template<class T> inline Vector4<T> Vector4<T>::operator+= (const Vector4<T> &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		w+=v.w;
		return (*this);
	}

	template<class T> inline Vector4<T> Vector4<T>::operator-= (const Vector4<T> &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
		w-=v.w;
		return (*this);
	}

	template<class T> inline Vector4<T>	Vector4<T>::operator*=	(const Vector4<T> &v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		w*=v.w;
		return (*this);
	}

	template<class T> inline Vector4<T> Vector4<T>::operator*= (const T &s)
	{
		x*=s;
		y*=s;
		z*=s;
		w*=s;
		return (*this);
	}

	template<class T> inline Vector4<T>	Vector4<T>::operator/=	(const Vector4<T> &v)
	{
		if(v.x==static_cast<T>(0))
		{
			x=x/Misc<T>::c_Epsilon;
		}
		else
		{
			x=x/v.x;
		}
		if(v.y==static_cast<T>(0))
		{
			y=y/Misc<T>::c_Epsilon;
		}
		else
		{
			y=y/v.y;
		}
		if(v.z==static_cast<T>(0))
		{
			z=z/Misc<T>::c_Epsilon;
		}
		else
		{
			z=z/v.z;
		}
		if(v.w==static_cast<T>(0))
		{
			w=w/Misc<T>::c_Epsilon;
		}
		else
		{
			w=w/v.w;
		}
		return *this;
	}

	template<class T> inline Vector4<T> Vector4<T>::operator/= (const T &s)
	{
		x/=s;
		y/=s;
		z/=s;
		w/=s;
		return *this;
	}
}

#endif
