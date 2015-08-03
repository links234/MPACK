#ifndef MVFS_FILEREADERINTERFACE_HPP
#define MVFS_FILEREADERINTERFACE_HPP

namespace MVFS
{
    class FileReaderInterface
    {
    public:
        virtual ~FileReaderInterface();

        virtual int Size() = 0;
        virtual void Reset() = 0;

        virtual void Read(char *pBuffer, int size) = 0;
        virtual void ReadFrom(int offset, char *pBuffer, int size) = 0;

        virtual void Skip(int size) = 0;
        virtual int GetOffset() = 0;
        virtual void SetOffset(int offset) = 0;

    protected:
        FileReaderInterface();
    };
}

#endif
