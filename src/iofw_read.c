#include <reent.h>
#include <errno.h>

#include "iofw_slots.h"

int _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt)
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
        // We don't handle system handles
        return 0;
    }

    return openfiles[fd].read(ptr, openfiles[fd].handle, buf, cnt);
}
