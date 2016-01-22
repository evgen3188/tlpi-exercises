#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE    1024
#endif

void writeBlock(Boolean isZeroBlock, int fd, char* buf, ssize_t len)
{
    if (!isZeroBlock)
    {
        // write the block of non-zero bytes to the output file
        if (write(fd, buf, len) != len)
        {
            fatal("couldn't write a buffer");
        }
    }
    else
    {
        // adjust the output file offset by the length of the block of zero bytes
        if (lseek(fd, len, SEEK_CUR) == -1)
        {
            errExit("lseek");
        }
    }
}

int main(int argc, char* argv[])
{
    int inputFd, outputFd;
    int openFlags;
    mode_t filePerms;
    Boolean isZeroBlock;
    ssize_t numRead, i, start = 0;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s old-file new-file\n\n", argv[0]);
        printf("For example: \n");
        printf("Create a sparse 16K file\n");
        printf("\tdd if=/dev/urandom of=test bs=4K count=1 seek=4K oflag=seek_bytes conv=sparse\n");
        printf("\tdd if=/dev/urandom of=test bs=4K count=1 seek=12K oflag=seek_bytes conv=sparse\n\n");

        printf("Apparent file size\n");
        printf("\tdu -h --apparent-size test   # output: 8 K\n\n");

        printf("Actual file size\n");
        printf("\tdu -h test                   # output: 16 K\n\n");

        printf("Issue: the program does not copy the last hole at the end of a file\n");

        exit(EXIT_SUCCESS);
    } 

    // Open input and output files
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        errExit("opening file %s", argv[1]);
    }
    
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        errExit("opening file %s", argv[2]);
    }

    // Read bytes from the input file
    while ((numRead = read(inputFd, buf, BUF_SIZE)))
    {
        isZeroBlock = (buf[0] == 0);
        for (start = i = 0; i < numRead; i++)
        {
            // A new block of bytes (nor zero nor non-zero) has been read
            // 'start' points to the start of the block
            // 'i - 1' points to the end of the block
            if (isZeroBlock != (buf[i] == 0))
            {
                isZeroBlock = (buf[i] == 0); 
                
                writeBlock(!isZeroBlock, outputFd, &buf[start], (i - start));
                start = i;
            }
        }

        writeBlock(isZeroBlock, outputFd, &buf[start], numRead - start);
    }

    if (numRead == -1) {
        errExit("read is failed");
    }

    if (close(inputFd) == -1) {
        errExit("close input");
    }

    if (close(outputFd) == -1) {
        errExit("close output");
    }

    exit(EXIT_SUCCESS);
}
