/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

class Uncopyable
{
protected:
	Uncopyable () {}
	~Uncopyable () {}

private:
	Uncopyable (const Uncopyable&);
	Uncopyable& operator=(const Uncopyable &);
};

#endif
