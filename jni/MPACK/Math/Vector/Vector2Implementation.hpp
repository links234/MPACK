#ifndef MPACK_VECTOR2IMPLEMENTATION_HPP
#define MPACK_VECTOR2IMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline Math::Vector2<T> Math::operator*(T s, const Math::Vector2<T> &v)
	{
		return Math::Vector2<T>(v.x*s,v.y*s);
	}

	template<class T> inline Math::Vector2<T> Math::Cross(const Math::Vector2<T> &v, T a)
	{
		return Math::Vector2<T>(a*v.y,-a*v.x);
	}

	template<class T> inline Math::Vector2<T> Math::Cross(T a, const Math::Vector2<T> &v)
	{
		return Math::Vector2<T>(-a*v.y,a*v.x);
	}

	template<class T> inline T Math::Cross(const Math::Vector2<T> &a, const Math::Vector2<T> &b )
	{
		return a.x*b.y-a.y*b.x;
	}

	template<class T> inline Math::Vector2<T> Math::Dot(const Math::Vector2<T> &v, T s)
	{
		return Math::Vector2<T>(v.x*s,v.y*s);
	}

	template<class T> inline Math::Vector2<T> Math::Dot(T s, const Math::Vector2<T> &v)
	{
		return Math::Vector2<T>(v.x*s,v.y*s);
	}

	template<class T> inline T Math::Dot(const Math::Vector2<T> &a, const Math::Vector2<T> &b)
	{
		return a.x*b.x+a.y*b.y;
	}

	template<class T> inline T Math::Distance(const Math::Vector2<T> &a, const Math::Vector2<T> &b)
	{
		T dx = a.x-b.x;
		T dy = a.y-b.y;
		return Math::Misc<T>::Sqrt(dx*dx+dy*dy);
	}

	template<class T> inline T Math::SquareDistance(const Math::Vector2<T> &a, const Math::Vector2<T> &b)
	{
		T dx = a.x-b.x;
		T dy = a.y-b.y;
		return dx*dx+dy*dy;
	}

	template<class T> inline void Math::Vector2<T>::Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template<class T> inline T Math::Vector2<T>::SquareLength() const
	{
		return x*x+y*y;
	}

	template<class T> inline T Math::Vector2<T>::Length() const
	{
		return Misc<T>::Sqrt(x*x+y*y);
	}

	template<class T> inline T Math::Vector2<T>::Magnitude() const
	{
		return Misc<T>::Sqrt(x*x+y*y);
	}

	template<class T> inline T Math::Vector2<T>::Angle() const
	{
		T angle=Misc<T>::RadToDeg((T)atan2((double)y,(double)x));
		return angle;
	}

	template<class T> inline T Math::Vector2<T>::Distance(const Math::Vector2<T> &point)const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		return Misc<T>::Sqrt(dx*dx+dy*dy);
	}

	template<class T> inline T Math::Vector2<T>::SquareDistance(const Math::Vector2<T> &point)const
	{
		T dx=x-point.x;
		T dy=y-point.y;
		return dx*dx+dy*dy;
	}

	template<class T> inline T Math::Vector2<T>::Dot(const Math::Vector2<T> &v) const
	{
		return x*v.x+y*v.y;
	}

	template<class T> inline void Math::Vector2<T>::Normalize()
	{
		T d=Magnitude();
		if(d!=static_cast<T>(0))
		{
			x/=d;
			y/=d;
		}
	}

	template<class T> inline void Math::Vector2<T>::Rotate(T amount)
	{
		amount = Misc<T>::DegToRad(amount);
		T xx = Misc<T>::Cos(amount)*x - Misc<T>::Sin(amount)*y;
		T yy = Misc<T>::Sin(amount)*x + Misc<T>::Cos(amount)*y;
		x = xx;
		y = yy;
	}

	template<class T> inline void Math::Vector2<T>::SquareMap()
	{
		Vector2<T> I;
		Vector2<T> C(static_cast<T>(0.5),static_cast<T>(0.5));
		Vector2<T> V(*this-C);
		const static Vector2<T> P[]={Vector2<T>(static_cast<T>(0),static_cast<T>(0)),Vector2<T>(static_cast<T>(0),static_cast<T>(1)),Vector2<T>(static_cast<T>(1),static_cast<T>(1)),Vector2<T>(static_cast<T>(1),static_cast<T>(0))};
		for(register int i=0;i<3;++i)
		{
			if(Geom<T>::LineIntersect(C,V,P[i],P[i+1],I))
			{
				x=I.x;
				y=I.y;
				return;
			}
		}
		Geom<T>::LineIntersect(C,V,P[3],P[0],I);
		x=I.x;
		y=I.y;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::Normalized()
	{
		Vector2<T> v(*this);
		v.Normalize();
		return v;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::SquareMaped()
	{
		Vector2<T> I;
		Vector2<T> C(static_cast<T>(0.5),static_cast<T>(0.5));
		Vector2<T> V(*this-C);
		const static Vector2<T> P[]={Vector2<T>(static_cast<T>(0),static_cast<T>(0)),Vector2<T>(static_cast<T>(0),static_cast<T>(1)),Vector2<T>(static_cast<T>(1),static_cast<T>(1)),Vector2<T>(static_cast<T>(1),static_cast<T>(0))};
		for(register int i=0;i<3;++i)
		{
			if(LineIntersect(C,V,P[i],P[i+1],I))
			{
				return I;
			}
		}
		LineIntersect(C,V,P[3],P[0],I);
		return I;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::Rotated(T amount)
	{
		Vector2<T> v(*this);
		v.Rotate(amount);
		return v;
	}

	template<class T> inline Math::Vector2<T>	Math::Vector2<T>::operator*	(const Math::Vector2<T> &v) const
	{
		return Vector2<T>(v.x*x,v.y*y);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator*  (const T &s) const
	{
		return Vector2<T>(x*s,y*s);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator/ (const Math::Vector2<T> &v) const
	{
		Vector2<T> t;
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
		return t;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator/  (const T &s) const
	{
		if(s==static_cast<T>(0))
		{
			return Vector2<T>(x/Misc<T>::c_Epsilon,y/Misc<T>::c_Epsilon);
		}
		return Vector2<T>(x/s,y/s);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator+  (const Math::Vector2<T> &v) const
	{
		return Vector2<T>(x+v.x,y+v.y);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator+  () const
	{
		return *this;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator-  (const Math::Vector2<T> &v) const
	{
		return Vector2<T>(x-v.x,y-v.y);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator-  () const
	{
		return Vector2<T>(-x,-y);
	}

	template<class T> inline bool Math::Vector2<T>::operator!= (const Math::Vector2<T> &v)const
	{
		if(!Misc<T>::Equal(x,v.x))
		{
			return true;
		}
		if(!Misc<T>::Equal(y,v.y))
		{
			return true;
		}
		return false;
	}

	template<class T> inline bool Math::Vector2<T>::operator==(const Math::Vector2<T> &v) const
	{
		if(!Misc<T>::Equal(x,v.x))
		{
			return false;
		}
		if(!Misc<T>::Equal(y,v.y))
		{
			return false;
		}
		return true;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator+= (const Math::Vector2<T> &v)
	{
		x+=v.x;
		y+=v.y;
		return (*this);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator-= (const Math::Vector2<T> &v)
	{
		x-=v.x;
		y-=v.y;
		return (*this);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator*= (const Math::Vector2<T> &v)
	{
		x*=v.x;
		y*=v.y;
		return (*this);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator*= (const T &s)
	{
		x*=s;
		y*=s;
		return (*this);
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator/=	(const Math::Vector2<T> &v)
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
		return *this;
	}

	template<class T> inline Math::Vector2<T> Math::Vector2<T>::operator/= (const T &s)
	{
		x/=s;
		y/=s;
		return *this;
	}
}

#endif
