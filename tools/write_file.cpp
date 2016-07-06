#include <stdio.h>

static void writeFile(const char *fileName, const void *buf, int size)
{
    FILE* file = fopen(fileName, "wb");
    fwrite(buf, 1, size, file);
    fclose(file);
}

static void appendFile(const char *fileName, const void *buf, int size)
{
    FILE* file = fopen(fileName, "ab");
    fwrite(buf, 1, size, file);
    fclose(file);
}

int main()
{
    char buf[] = {0x11, 0x22, 0x33};
    char buf2[] = {0x44, 0x55, 0x66};
    int size = 3;
    
    writeFile("./output1.bin", buf, 3);
    writeFile("./output1.bin", buf2, 3);

    writeFile("./output2.bin", buf, 3);
    appendFile("./output2.bin", buf2, 3);    
    
    return 0;
}

