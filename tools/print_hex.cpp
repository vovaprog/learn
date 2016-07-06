#include <iostream>
#include <iomanip>

static void printBytesHex(void *buf, int size)
{
    std::cout << std::hex << std::setfill('0') << std::setw(2);
    std::cout << std::endl << "[ ";
    for(int i=0;i<size;++i)
    {
        std::cout << (int)((unsigned char*)buf)[i] << " ";
    }
    std::cout << "]   (size: " << std::dec << size << ")" << std::endl;     
}

static void printBytesHex(const char *msg, void *buf, int size)
{
    std::cout << msg;
    printBytesHex(buf, size);
}

int main()
{
    char buf[] = {0x11, 0x22, 0x33};
    int size = 3;
    
    printBytesHex(buf, size);
    printBytesHex("input: ", buf, size);
    printBytesHex("output: ", buf, size);
    
    return 0;
}

