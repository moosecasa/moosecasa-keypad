#include "mem-map.h"

/*
    Windows Memory mapping documentation here:
    https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga
    https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffileex

*/
#ifdef _WIN32
void *
mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    HANDLE hmap;
    void *temp;
    size_t len;
    struct stat st;  
    uint64_t o = offset;
    uint32_t l = o & 0xFFFFFFFF;
    uint32_t h = (o >> 32) & 0xFFFFFFFF;
    uint32_t desiredAccess = 0x0;
  

    if (!fstat(fd, &st))
    {
        len = (size_t) st.st_size;
    }
    else {
        printf("mmap: could not get file size");
        return MAP_FAILED;
    }

    if ((length + offset) > len)
    {
        length = len - offset;
    }

    #ifdef DEBUG
    if (!(flags & MAP_PRIVATE))
    {
        printf("mmap: INFO: Windows cannot map private maps, they are shared.");
    }
    #endif
    if(prot & PROT_EXEC)
    {
        if(prot &(PROT_READ|PROT_WRITE))
        {
            desiredAccess = PAGE_EXECUTE_WRITECOPY;
        }
        else if(prot & (PROT_READ))
        {
            desiredAccess = PAGE_EXECUTE_READ;
        }    
    }
    else if(prot & PROT_READ)
    {
        if(prot & PROT_WRITE)
        {
            desiredAccess = PAGE_WRITECOPY;
        }
        else
        {
            desiredAccess = PAGE_READONLY;
        }
    }

    hmap = CreateFileMapping((HANDLE)_get_osfhandle(fd), 0, desiredAccess, 0, 0, 0);

    if (!hmap)
        return MAP_FAILED;

    temp = MapViewOfFileEx(hmap, FILE_MAP_COPY, h, l, length, start);

    if (!CloseHandle(hmap))
        fprintf(stderr,"unable to close file mapping handle\n");
    return temp ? temp : MAP_FAILED;
}

int
munmap(void *addr, size_t length)
{
  return !UnmapViewOfFile(addr);
}
#endif