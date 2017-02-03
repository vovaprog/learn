#include <FileUtils.h>

#include <stdio.h>

int main()
{
    char * buf;

    int err = readTextFile("./test.txt", buf);

    if(err == 0)
    {
        printf("file: [%s]\n", buf);
        delete[] buf;
    }    

    long long int fileSize;

    err = readFile("./test.txt", buf, fileSize);

    if(err == 0)
    {
        buf[fileSize - 1] = 0;
        printf("file: [%s]\n", buf);
    }

    return 0;
}

