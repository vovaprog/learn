#ifndef MAPPED_FILE_H
#define MAPPED_FILE_H

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

    int create(const char * fileName)
    {
        fd = open(logFileName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
            perror("open failed");
            return -1;
        }

        if(ftruncate(fd, logFileSize) != 0)
        {
            perror("ftruncate failed");

            close(fd);
            fd = -1;

            return -1;
        }

        void *p = mmap(NULL, logFileSize, PROT_WRITE, MAP_SHARED, fd, 0);
        if(p == MAP_FAILED)
        {
            perror("mmap failed");

            close(fd);
            fd = -1;

            return -1;
        }

        buffer.init(p, logFileSize);

        return 0;
    }

private:
    int fd = -1;
};

#endif // MAPPED_FILE_H
