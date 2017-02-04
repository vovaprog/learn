#ifndef FILE_UTILS_H
#define FILE_UTILS_H

long long int fileSize(const char *filename);
long long int fileSize(int fd);

int readTextFile(const char * fileName, char * & buf);
int readFile(const char * fileName, char * & buf, long long int & fileSize);

int appendFile(const char *fileName, const char *data, long long int dataSize);

#endif
