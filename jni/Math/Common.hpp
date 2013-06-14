/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>

namespace Math
{
	template <class T> class Misc
	{
	public:
		const static T      c_Pi,
							c_TwoPi,
							c_HalfPi,
							c_InvPi,
							c_e,
							c_DegToRad,
							c_RadToDeg,
							c_Epsilon,
							c_Min,
							c_Max;

		static T Sin(const T);
		static T Cos(const T);
		static T Tan(const T);
		static T Sqrt(const T);
		static T InvSqrt(const T);

		static bool Equal(T, const T);

		static T DegToRad(const T);
		static T RadToDeg(const T);

		static T Min(const T, const T);
		static T Max(const T, const T);
		static T Clamp(const T, const T, const T);
		static T Sign(const T);
	};

	template<> inline float		Misc<float>::Sin(const float v)			{ return sinf(v);			}
	template<> inline double	Misc<double>::Sin(const double v)		{ return sin(v);			}
	template<> inline float		Misc<float>::Cos(const float v)			{ return cosf(v);			}
	template<> inline double	Misc<double>::Cos(const double v)		{ return cos(v);			}
	template<> inline float		Misc<float>::Tan(const float v)			{ return tanf(v);			}
	template<> inline double	Misc<double>::Tan(const double v)		{ return tan(v);			}
	template<> inline float		Misc<float>::Sqrt(const float v)		{ return sqrtf(v);			}
	template<> inline double	Misc<double>::Sqrt(const double v)		{ return sqrt(v);			}
	template<> inline float		Misc<float>::InvSqrt(const float v)		{ return 1.0f / sqrtf(v);	}
	template<> inline double	Misc<double>::InvSqrt(const double v)	{ return 1.0 / sqrt(v);		}

	template<class T> inline bool Misc<T>::Equal(T a, const T b)
	{
		a = b-a;
		return Misc<T>::c_Epsilon < a && a < Misc<T>::c_Epsilon;
	}

	template<class T> inline T Misc<T>::DegToRad(const T deg)
	{
		return deg * Misc<T>::c_DegToRad;
	}

	template<class T> inline T Misc<T>::RadToDeg(const T rad)
	{
		return rad * Misc<T>::c_RadToDeg;
	}

	template<class T> inline T Misc<T>::Min(const T a, const T b)
	{
		if(a<b)
		{
			return a;
		}
		return b;
	}

	template<class T> inline T Misc<T>::Max(const T a, const T b)
	{
		if(a>b)
		{
			return a;
		}
		return b;
	}

	template<class T> inline T Misc<T>::Clamp(const T a, const T b, const T c)
	{
		if(a<b)
		{
			return b;
		}
		if(a>c)
		{
			return c;
		}
		return a;
	}

	template<class T> inline T Misc<T>::Sign(const T a)
	{
		if(Equal(a,0))
		{
			return static_cast<T>(0);
		}
		if(a<0)
		{
			return static_cast<T>(-1);
		}
		return static_cast<T>(1);
	}
}

#endif
