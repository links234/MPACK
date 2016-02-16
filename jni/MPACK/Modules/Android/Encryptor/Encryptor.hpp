#ifndef ENCRYPTOR_HPP
#define ENCRYPTOR_HPP

#include <vector>

namespace MPACK
{
	namespace Encryptor
	{
		void Destroy();

		std::vector<unsigned char> Encrypt(std::vector<unsigned char>);
		std::vector<unsigned char> Decrypt(std::vector<unsigned char>);
	}
}



#endif
