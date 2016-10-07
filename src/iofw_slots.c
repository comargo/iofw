#include <stdlib.h>
#include "iofw_slots.h"

struct iofw_file openfiles[MAX_OPEN_FILES] = {NULL};
__attribute__((constructor)) static void init_iofw(void)
{
    int fd;
    for(fd=0; fd<MAX_OPEN_FILES; ++fd) {
        openfiles[fd].handle = INVALID_HANDLE;
    }

    fd = 0;
    openfiles[fd].handle = SYSTEM_HANDLE;
    fd = 1;
    openfiles[fd].handle = SYSTEM_HANDLE;
    fd = 2;
    openfiles[fd].handle = SYSTEM_HANDLE;

}

int iofw_newslot()
{
    int fd = iofw_findslot(INVALID_HANDLE);
    if(fd == MAX_OPEN_FILES)
        return -1;
    return fd;
}

int iofw_findslot(void *handle)
{
    int fd;
    for(fd=0; fd<MAX_OPEN_FILES; ++fd) {
        if(openfiles[fd].handle == handle)
            break;
    }
    return fd;
}
