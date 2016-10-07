#include <reent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "iofw_types.h"
#include "iofw_slots.h"

int _fstat_r(struct _reent *ptr, int fd, struct stat *buf)
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
        return -1;
    }

    buf->st_dev = 0;
    buf->st_ino = 0;
    buf->st_mode = _IFCHR|S_IREAD|0666;
    buf->st_nlink = 1;
    buf->st_uid = 0;
    buf->st_gid = 0;
    buf->st_rdev = 0;
    buf->st_blksize = 0;
    buf->st_blocks = 0;
    buf->st_atime = 0;
    buf->st_mtime = 0;
    buf->st_ctime = 0;

    if(openfiles[fd].fstat) {
        return openfiles[fd].fstat(ptr, openfiles[fd].handle, buf);
    }
}
