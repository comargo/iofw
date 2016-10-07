#include <reent.h>
#include <errno.h>
#include <string.h>

#include "iofw_types.h"
#include "iofw_slots.h"

int _open_r(struct _reent *ptr, const char *file, int flags,  int mode)
{
    struct iofw_regentry *entry;
    SLIST_FOREACH(entry, &iofw_registry, entries) {
        char *found = strstr(file, entry->name);
        if(found == file) {
            break;
        }
    }
    if(!entry) {
        __errno_r(ptr) = ENODEV;
        return -1;
    }

    int fd = iofw_newslot();
    if(fd == -1) {
        __errno_r(ptr) = EMFILE;
        return fd;
    }

    void* handle = entry->open(ptr, file, flags, mode, entry->handle);
    if(handle == INVALID_HANDLE)
        return -1;
    openfiles[fd].handle = handle;
    openfiles[fd].close = entry->close;
    openfiles[fd].read = entry->read;
    openfiles[fd].write = entry->write;
    openfiles[fd].fstat = entry->fstat;
    openfiles[fd].isatty = entry->isatty;
    return fd;
}

