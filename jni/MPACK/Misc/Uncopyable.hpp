#ifndef MPACK_UNCOPYABLE_H
#define MPACK_UNCOPYABLE_H

namespace MPACK
{
	class Uncopyable
	{
	protected:
		Uncopyable () {}
		~Uncopyable () {}

	private:
		Uncopyable (const Uncopyable&);
		Uncopyable& operator=(const Uncopyable &);
	};
}

#endif
