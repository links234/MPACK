#ifndef MVFS_MVFS_V1_HPP
#define MVFS_MVFS_V1_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace MVFS
{
    namespace V1
    {
        void Pack (std::string pathToDir, std::string pathToArchive="", std::vector<char> key=std::vector<char>());
    }
}

#endif
