#include <FileUtils.h>
#include <MappedFile.h>

#include <stdio.h>
#include <string.h>

using namespace std;

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

    const char * const appendFileName = "./append.txt";

    const char *line1 = "hello\n";
    const char *line2 = "world\n";
    const char *line3 = "!!!\n";

    int ret = appendFile(appendFileName, line1, strlen(line1));
    if(ret)
    {
        printf("appendFile failed: %s\n", strerror(ret));
    }

    ret = appendFile(appendFileName, line2, strlen(line2));
    if(ret)
    {
        printf("appendFile failed: %s\n", strerror(ret));
    }

    appendFile(appendFileName, line3, strlen(line3));

    {
        MappedFile mapFile;
        //int ret = mapFile.createFile("./map.txt", 100);
        int ret = mapFile.openFile("./map.txt");
        if(ret)
        {
            printf("map failed: %s\n", strerror(ret));
        }
        void *p = mapFile.getData();
        //strcpy((char*)p, "map works!\n");
        strcat((char*)p, "\nappend data!\n");
    }

    return 0;
}

