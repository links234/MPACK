#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "Mouse.hpp"

namespace Core
{
	bool Mouse::Buttons::operator!= (const Mouse::Buttons &other)
	{
		if(Left!=other.Left)
		{
			return true;
		}
		if(Middle!=other.Middle)
		{
			return true;
		}
		if(Right!=other.Right)
		{
			return true;
		}
		return false;
	}

	bool Mouse::Buttons::operator== (const Mouse::Buttons &other)
	{
		if(Left!=other.Left)
		{
			return false;
		}
		if(Middle!=other.Middle)
		{
			return false;
		}
		if(Right!=other.Right)
		{
			return false;
		}
		return true;
	}


	bool Mouse::operator!= (const Mouse &other)
	{
		if(Pos!=other.Pos)
		{
			return true;
		}
		if(Wheel!=other.Wheel)
		{
			return true;
		}
		if(Button!=other.Button)
		{
			return true;
		}
		return false;
	}

	bool Mouse::operator== (const Mouse &other)
	{
		if(Pos!=other.Pos)
		{
			return false;
		}
		if(Wheel!=other.Wheel)
		{
			return false;
		}
		if(Button!=other.Button)
		{
			return false;
		}
		return true;
	}
}

#endif
