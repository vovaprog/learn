#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


long long int fileSize(const char *filename)
{
    struct stat st;

    if(stat(filename, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}


long long int fileSize(int fd)
{
    struct stat st;

    if(fstat(fd, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}


int readFile(const char * fileName, char * & buf, long long int & fileSize)
{
    int fd = open(fileName, O_RDONLY);

    if(fd < 0)
    {
        return (errno != 0 ? errno : EINVAL);
    }

    struct stat st;

    if(fstat(fd, &st) != 0)
    {
        int err = errno;
        close(fd);
        return (err != 0 ? err : EINVAL);
    }

    fileSize = st.st_size;

    if(fileSize < 0)
    {
        close(fd);
        return EINVAL;
    }

    // allocate one more byte for zero
    buf = new char[fileSize + 1];

    if(fileSize == 0)
    {
        buf[0] = 0;
        close(fd);
        return 0;
    }

    long long int bufPos = 0;
    long long int bytesLeft = fileSize;

    while(bytesLeft > 0)
    {
        int bytesRead = read(fd, buf + bufPos, bytesLeft);

        if(bytesRead < 0)
        {
            int err = errno;
            delete[] buf;
            close(fd);
            return (err != 0 ? err : EINVAL);
        }
        else if(bytesRead == 0)
        {
            delete[] buf;
            close(fd);
            return EINVAL;
        }

        bufPos += bytesRead;
        bytesLeft -= bytesRead;
    }

    buf[fileSize] = 0;
    close(fd);
    return 0;
}


int readTextFile(const char * fileName, char * & buf)
{
    long long int fileSize;

    return readFile(fileName, buf, fileSize);
}
