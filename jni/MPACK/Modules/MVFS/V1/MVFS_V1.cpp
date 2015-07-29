#include "MVFS_V1.hpp"

#include "MVFS_V1_Constants.hpp"
#include "MVFS_V1_Reader.hpp"

#include "MVFSGlobal.hpp"

#if defined(LINUX_PLATFORM)
    #include <sys/types.h>
    #include <dirent.h>
    #include <errno.h>
#endif

using namespace std;

namespace MVFS
{
    namespace V1
    {
        vector<char> xorKey;
        ofstream archiveOutput;

        void PackWriteFile(string pathToFile)
        {
            ifstream file(pathToFile.c_str(), ios::binary | ios::ate);
            int fileSize = file.tellg();
            file.close();

            if(Global::verbose)
            {
                cout<<"Packing file \""<<pathToFile<<"\" with size = "<<fileSize<<" bytes"<<endl;
            }

            char *buffer=new char[fileSize];
            file.open(pathToFile.c_str(),ios::binary);
            file.read(buffer,fileSize);
            file.close();

            if(xorKey.size())
            {
                int keyIndex=0;
                for(int i=0;i<fileSize;++i)
                {
                    buffer[i]^=xorKey[keyIndex];

                    ++keyIndex;
                    if(keyIndex>=xorKey.size())
                    {
                        keyIndex=0;
                    }
                }
            }

            archiveOutput.write((char*)(&fileSize),sizeof(fileSize));
            archiveOutput.write(buffer,fileSize);

            delete[] buffer;
        }

        void PackRec(string pathToDir)
        {
#if defined(LINUX_PLATFORM)
            DIR *dp;
            struct dirent *dirp;
            if((dp  = opendir(pathToDir.c_str())) == NULL)
            {
                cerr << "Error(" << errno << ") opening directory \"" << pathToDir << "\"" << endl;
                return;
            }

            while ((dirp = readdir(dp)) != NULL)
            {
                string name=string(dirp->d_name);
                if(name==".")
                {
                    continue;
                }
                if(name=="..")
                {
                    continue;
                }
                if(name[name.size()-1]=='~')
                {
                    continue;
                }

                if(dirp->d_type==DT_REG)
                {
                    archiveOutput<<NEWFILE;
                    archiveOutput.write((const char*)name.c_str(),name.size()+1);
                    PackWriteFile(pathToDir+"/"+name);
                }
                else if(dirp->d_type==DT_DIR)
                {
                    archiveOutput<<MKDIR;
                    archiveOutput.write((const char*)name.c_str(),name.size()+1);
                    archiveOutput<<OPENLASTMKDIR;
                    PackRec(pathToDir+"/"+name);
                    archiveOutput<<BACK;
                }
            }
            closedir(dp);
#endif
        }

        void Pack (string pathToDir, string pathToArchive, vector<char> key)
        {
            if(pathToArchive=="")
            {
                pathToArchive=pathToDir+".mvfs";
            }

            if(Global::verbose)
            {
                cout<<"Packing \""<<pathToDir<<"\" into \""<<pathToArchive<<"\""<<endl;
            }

            archiveOutput.open(pathToArchive.c_str(),ios::binary);

            xorKey=key;
            unsigned char xorBit=0;
            if(xorKey.size()>0)
            {
                xorBit=1;
            }
            unsigned char version = (THIS_VERSION<<4)|xorBit;

            archiveOutput<<version;

            PackRec(pathToDir);

            archiveOutput.close();
        }
    }
}
