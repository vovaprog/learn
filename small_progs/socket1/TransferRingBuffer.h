#ifndef TRANSFER_RING_BUFFER_H
#define TRANSFER_RING_BUFFER_H

class TransferRingBuffer {
public:
    TransferRingBuffer(int size): bufSize(size)
    {
        buf = new char[size];        
    }
    
    ~TransferRingBuffer()
    {
        if(buf!=nullptr)
            delete[] buf;
    }
    
    bool startWrite(void* &data, int &size)
    {
        data = buf + writeHead;
        
        if(writeHead >= readHead)
        {
            size = bufSize - writeHead;
        }
        else
        {
            size = readHead - writeHead;
        }
        
        return (size>0);
    }
    
    void endWrite(int size)
    {
        writeHead += size;
        if(writeHead == bufSize)
            writeHead = 0;        
    }    
    
    bool startRead(void* &data, int &size)
    {
        data = buf + readHead;
        
        if(readHead < writeHead)
        {
            size = writeHead - readHead;
        }
        else
        {
            size = bufSize - readHead;
        }
        
        return (size>0);
    }
    
    void endRead(int size)
    {
        readHead += size;
        if(readHead == bufSize)
            readHead = 0;
    }
    
protected:        
    char *buf = nullptr;
    int readHead = 0, writeHead = 0, bufSize = 0;
};

#endif
