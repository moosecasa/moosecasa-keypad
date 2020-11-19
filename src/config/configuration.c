#include "configuration.h"
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../vendor/my_itoa.h"

/**
 * @brief Parses configuration file into a structure
 *
 * Returns a pointer to #Config structure. Parses configuration file by loading it into memory and setting the values needed.
 */
struct Config* ParseConfig(char* path){
    int fd;
    int e;
    struct Config* cfg;
    char errornumber[12];
    char* fileMM;

    char *buf, *buf_end;
    char *begin, *end, c;
    
    #ifdef _WIN32
    fd = open(path,O_RDONLY, _S_IREAD);
    #else
    fd = open(path,O_RDONLY, S_IRUSR|S_IRGRP|S_IROTH);
    #endif
    e=errno;
    if(!fd)
    {
        my_itoa(e,errornumber,12,10);
        perror("Unable to open configuration file\n");
        perror(errornumber);
        perror(strerror(e));
    }
    struct stat sbuffer;

    if(fstat(fd, &sbuffer) == -1)
    {
        e=errno;
        my_itoa(e,errornumber,12,10);
        perror("Unable to get configuration file size\n");
        perror(errornumber);
        perror(strerror(e));

    }

    #ifdef _WIN32
    fileMM = mmap(NULL,sbuffer.st_size,PROT_READ, MAP_SHARED, fd,0);
    #else
    fileMM = mmap(NULL,sbuffer.st_size,PROT_READ, MAP_PRIVATE, fd,0);
    #endif

    cfg = calloc(1,sizeof(struct Config));
    
    buf_end = buf + sbuffer.st_size;
 
    begin = end = buf;
    while (1) {
            if (! (*end == '\r' || *end == '\n')) {
                    if (++end < buf_end) continue;
            } else if (1 + end < buf_end) {
                    /* see if we got "\r\n" or "\n\r" here */
                    c = *(1 + end);
                    if ( (c == '\r' || c == '\n') && c != *end)
                            ++end;
            }
 
            /* call the call back and check error indication. Announce
            error here, because we didn't tell call_back the file name */
            //if (! call_back(begin, end)) {
                    //err(1, "[callback] %s", fname);
            //        break;
            //}
 
            if ((begin = ++end) >= buf_end)
                break;
    }

    return cfg;
}