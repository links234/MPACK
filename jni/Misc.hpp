#ifndef MISC_HPP
#define MISC_HPP

#include <string>

using namespace std;

namespace Misc
{
	const char* PathExtension(const char* pStr);

	void StringUpper(string &str);
	void StringLower(string &str);

	void PathExtension(string path, string &ext);
}


#endif
