#ifndef __MEM_MAP_H__
#define __MEM_MAP_H__
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>

//These constants can be found in mman-linux.h 
#define PROT_READ        0x1                /* Page can be read.  */
#define PROT_WRITE        0x2                /* Page can be written.  */
#define PROT_EXEC        0x4                /* Page can be executed.  */
#define PROT_NONE        0x0                /* Page can not be accessed.  */
/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED        0x01                /* Share changes.  */
#define MAP_PRIVATE        0x02                /* Changes are private.  */
//This contant can be found in mman.h
/* Return value of `mmap' in case of an error.  */
#define MAP_FAILED        ((void *) -1)

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#endif
