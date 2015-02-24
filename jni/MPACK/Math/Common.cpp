/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#include "Common.hpp"

namespace MPACK
{
	namespace Math
	{
		template<> const float	Misc<float>::c_Pi			= static_cast<float>	( 3.1415926535897932384626433832795028841971693993751 );
		template<> const double	Misc<double>::c_Pi			= static_cast<double>	( 3.1415926535897932384626433832795028841971693993751 );

		template<> const float	Misc<float>::c_TwoPi		= static_cast<float>	( 2.0 * 3.1415926535897932384626433832795028841971693993751 );
		template<> const double	Misc<double>::c_TwoPi		= static_cast<double>	( 2.0 * 3.1415926535897932384626433832795028841971693993751 );

		template<> const float	Misc<float>::c_HalfPi		= static_cast<float>	( 0.5 * 3.1415926535897932384626433832795028841971693993751 );
		template<> const double	Misc<double>::c_HalfPi		= static_cast<double>	( 0.5 * 3.1415926535897932384626433832795028841971693993751 );

		template<> const float	Misc<float>::c_InvPi		= static_cast<float>	( 0.31830988618379067154 );
		template<> const double	Misc<double>::c_InvPi		= static_cast<double>	( 0.31830988618379067154 );

		template<> const float	Misc<float>::c_RadToDeg		= static_cast<float>	( 57.2957795130823208768 );
		template<> const double	Misc<double>::c_RadToDeg	= static_cast<double>	( 57.2957795130823208768 );

		template<> const float	Misc<float>::c_DegToRad		= static_cast<float>	( 0.01745329251994329577 );
		template<> const double	Misc<double>::c_DegToRad	= static_cast<double>	( 0.01745329251994329577 );

		template<> const float	Misc<float>::c_e			= static_cast<float>	( 2.718281828 );
		template<> const double	Misc<double>::c_e			= static_cast<double>	( 2.718281828 );

		template<> const float	Misc<float>::c_Epsilon		= static_cast<float>	( 0.00000001 );
		template<> const double	Misc<double>::c_Epsilon		= static_cast<double>	( 0.00000001 );

		template<> const float	Misc<float>::c_Min			= static_cast<float>	( -1.0e32 );
		template<> const double	Misc<double>::c_Min			= static_cast<double>	( -1.0e64 );

		template<> const float	Misc<float>::c_Max			= static_cast<float>	( 1.0e32 );
		template<> const double	Misc<double>::c_Max			= static_cast<double>	( 1.0e64 );
	}
}
