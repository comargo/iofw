#include <reent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "iofw_types.h"
#include "iofw_slots.h"

int _isatty_r(struct _reent *ptr, int fd)
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
        return 1;
    }

    if(openfiles[fd].isatty) {
        return openfiles[fd].isatty(ptr, openfiles[fd].handle);
    }

    __errno_r(ptr) = ENOTTY;
    return 0;


}
