#include <reent.h>
#include <errno.h>

#include "iofw_slots.h"

int _close_r(struct _reent *ptr, int fd)
{
    if(fd >= MAX_OPEN_FILES) {
        __errno_r(ptr) = EMFILE;
        return -1;
    }

    if(openfiles[fd].handle == INVALID_HANDLE) {
        __errno_r(ptr) = EBADF;
        return -1;
    }

    if(openfiles[fd].handle == SYSTEM_HANDLE) {
        openfiles[fd].handle = INVALID_HANDLE;
        return 0;
    }

    int ret = openfiles[fd].close(ptr, openfiles[fd].handle);
    openfiles[fd].handle = INVALID_HANDLE;
    return ret;
}
