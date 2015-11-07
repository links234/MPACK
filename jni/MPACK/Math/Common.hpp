#ifndef MPACK_COMMON_HPP
#define MPACK_COMMON_HPP

#include <cmath>

namespace MPACK
{
	namespace Math
	{
		template <class T> class Misc
		{
		public:
			const static T     		c_Pi,
									c_TwoPi,
									c_HalfPi,
									c_InvPi,
									c_e,
									c_DegToRad,
									c_RadToDeg,
									c_Epsilon,
									c_Min,
									c_Max,
									c_BiasRelative,
									c_BiasAbsolute;

			static T Sin(const T);
			static T Cos(const T);
			static T Tan(const T);
			static T Sqr(const T);
			static T Sqrt(const T);
			static T InvSqrt(const T);

			static bool Equal(const T, const T);

			static T DegToRad(const T);
			static T RadToDeg(const T);

			static T Min(const T, const T);
			static T Max(const T, const T);
			static T Clamp(const T, const T, const T);
			static T Sign(const T);
			static T Abs(const T);

			static T Mod(const T, const T);

			static T Interpolate(const T, const T, const double);

			static bool BiasGreaterThan(T a, T b);
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
		template<> inline double	Misc<double>::InvSqrt(const double v)	{ return 1.0 / sqrt(v);	}

		template<class T> inline T Misc<T>::Sqr(const T v)
		{
			return v*v;
		}

		template<class T> inline bool Misc<T>::Equal(const T a, const T b)
		{
			return Misc<T>::Abs(a-b) < Misc<T>::c_Epsilon;
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

		template<class T> inline T Misc<T>::Abs(const T a)
		{
			if(a<0)
			{
				return -a;
			}
			return a;
		}

		template<> inline float		Misc<float>::Mod(const float a, const float b)
		{
			return (float)fmod((double)(a),(double)(b));
		}

		template<> inline double	Misc<double>::Mod(const double a, const double b)
		{
			return fmod(a,b);
		}

		template<class T> inline T Misc<T>::Interpolate(const T from, const T to, const double coeff)
		{
			return from*(1.0-coeff)+to*coeff;
		}

		template<class T> inline bool Misc<T>::BiasGreaterThan(T a, T b)
		{
			return a>=b*Misc<T>::c_BiasRelative+a*Misc<T>::c_BiasAbsolute;
		}
	}
}

#endif
