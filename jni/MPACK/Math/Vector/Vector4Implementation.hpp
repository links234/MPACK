#ifndef MPACK_VECTOR4IMPLEMENTATION_HPP
#define MPACK_VECTOR4IPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline T Math::Vector4<T>::Length() const
	{
		return Math::Misc<T>::Sqrt(x*x+y*y+z*z+w*w);
	}

	template<class T> inline T Math::Vector4<T>::Magnitude() const
	{
		return Math::Misc<T>::Sqrt(x*x+y*y+z*z+w*w);
	}

	template<class T> inline T Math::Vector4<T>::Distance(const Math::Vector4<T> &point)const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		T dz=z-point.z;
		T dw=w-point.w;
		return Math::Misc<T>::Sqrt(dx*dx+dy*dy+dz*dz+dw*dw);
	}

	template<class T> inline T Math::Vector4<T>::Dot(const Math::Vector4<T> &v) const
	{
		return x*v.x+y*v.y+z*v.z+w*v.w;
	}

	template<class T> inline void Math::Vector4<T>::Normalize()
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

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::Normalized()
	{
		Math::Vector4<T> v(*this);
		v.normalize();
		return v;
	}

	template<class T> inline Math::Vector4<T>	Math::Vector4<T>::operator*	(const Math::Vector4<T> &v) const
	{
		return Math::Vector4<T>(v.x*x,v.y*y,v.z*z,v.w*w);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator*  (const T &s) const
	{
		return Math::Vector4<T>(x*s,y*s,z*s,w*s);
	}

	template<class T> inline Math::Vector4<T>	Math::Vector4<T>::operator/	(const Math::Vector4<T> &v) const
	{
		Math::Vector4<T> t;
		if(v.x==static_cast<T>(0))
		{
			t.x=x/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			t.x=x/v.x;
		}
		if(v.y==static_cast<T>(0))
		{
			t.y=y/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			t.y=y/v.y;
		}
		if(v.z==static_cast<T>(0))
		{
			t.z=z/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			t.z=z/v.z;
		}
		if(v.w==static_cast<T>(0))
		{
			t.w=w/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			t.w=w/v.w;
		}
		return t;
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator/  (const T &s) const
	{
		if(s==static_cast<T>(0))
		{
			return Math::Vector4<T>(x/Math::Misc<T>::c_Epsilon,y/Math::Misc<T>::c_Epsilon,z/Math::Misc<T>::c_Epsilon,w/Math::Misc<T>::c_Epsilon);
		}
		return Math::Vector4<T>(x/s,y/s,z/s,w/s);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator+  (const Math::Vector4<T> &v) const
	{
		return Math::Vector4<T>(x+v.x,y+v.y,z+v.z,w+v.w);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator-  (const Math::Vector4<T> &v) const
	{
		return Math::Vector4<T>(x-v.x,y-v.y,z-v.z,w-v.w);
	}

	template<class T> inline bool Math::Vector4<T>::operator!= (const Math::Vector4<T> &v)const
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
		if(!Math::Misc<T>::Equal(w,v.w))
		{
			return true;
		}
		return false;
	}

	template<class T> inline bool Math::Vector4<T>::operator==(const Math::Vector4<T> &v) const
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
		if(!Math::Misc<T>::Equal(w,v.w))
		{
			return false;
		}
		return true;
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator+= (const Math::Vector4<T> &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		w+=v.w;
		return (*this);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator-= (const Math::Vector4<T> &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
		w-=v.w;
		return (*this);
	}

	template<class T> inline Math::Vector4<T>	Math::Vector4<T>::operator*= (const Math::Vector4<T> &v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		w*=v.w;
		return (*this);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator*= (const T &s)
	{
		x*=s;
		y*=s;
		z*=s;
		w*=s;
		return (*this);
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator/= (const Math::Vector4<T> &v)
	{
		if(v.x==static_cast<T>(0))
		{
			x=x/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			x=x/v.x;
		}
		if(v.y==static_cast<T>(0))
		{
			y=y/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			y=y/v.y;
		}
		if(v.z==static_cast<T>(0))
		{
			z=z/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			z=z/v.z;
		}
		if(v.w==static_cast<T>(0))
		{
			w=w/Math::Misc<T>::c_Epsilon;
		}
		else
		{
			w=w/v.w;
		}
		return *this;
	}

	template<class T> inline Math::Vector4<T> Math::Vector4<T>::operator/= (const T &s)
	{
		x/=s;
		y/=s;
		z/=s;
		w/=s;
		return *this;
	}
}

#endif
