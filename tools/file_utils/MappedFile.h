#ifndef MAPPED_FILE_H
#define MAPPED_FILE_H

#include <sys/mman.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class MappedFile {
public:
    MappedFile() = default;

    MappedFile(const MappedFile &ed) = delete;
    MappedFile(MappedFile &&ed) = delete;
    MappedFile& operator=(const MappedFile &ed) = delete;
    MappedFile& operator=(MappedFile && ed) = delete;

    ~MappedFile()
    {
        destroy();
    }

    int createFile(const char * const fileName, long long int fileSize)
    {
        fd = open(fileName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
            int err = errno;
            return (err != 0 ? err : EINVAL);
        }

        if(ftruncate(fd, fileSize) != 0)
        {
            int err = errno;
            close(fd);
            fd = -1;
            return (err != 0 ? err : EINVAL);
        }

        p = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if(p == MAP_FAILED)
        {            
            int err = errno;
            close(fd);
            fd = -1;
            p = nullptr;
            return (err != 0 ? err : EINVAL);
        }

        this->fileSize = fileSize;

        return 0;
    }

    int openFile(const char * const fileName)
    {
        fd = open(fileName, O_RDWR);
        if(fd < 0)
        {
            int err = errno;
            return (err != 0 ? err : EINVAL);
        }


        struct stat st;

        if(fstat(fd, &st) != 0)
        {
            int err = errno;
            close(fd);
            return (err != 0 ? err : EINVAL);
        }

        fileSize = st.st_size;


        p = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if(p == MAP_FAILED)
        {
            int err = errno;
            close(fd);
            fd = -1;
            p = nullptr;
            return (err != 0 ? err : EINVAL);
        }

        return 0;
    }

    void destroy()
    {
        if(fd >= 0)
        {
            if(p != nullptr)
            {
                munmap(p, fileSize);
                p = nullptr;
                fileSize = 0;
            }

            close(fd);
            fd = -1;
        }
    }

    void* getData() const
    {
        return p;
    }

    long long int size() const
    {
        return fileSize;
    }

private:

    int fd = -1;
    void *p = nullptr;
    long long int fileSize = 0;
};

#endif // MAPPED_FILE_H
