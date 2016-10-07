#ifndef IOFW_TYPES_H
#define IOFW_TYPES_H

#include <sys/queue.h>
#include <reent.h>

typedef void *(iofw_open_f)(struct _reent *ptr, const char *file, int flags,  int mode, void *handle);
typedef int (iofw_read_f)(struct _reent *ptr, void *handle, void *buf, size_t cnt);
typedef int (iofw_write_f)(struct _reent *ptr, void *handle, const void *buf, size_t cnt);
typedef int (iofw_close_f)(struct _reent *ptr, void *handle);
typedef int (iofw_fstat_f)(struct _reent *ptr, void *handle, struct stat *buf);
typedef int (iofw_isatty_f)(struct _reent *ptr, void *handle);




struct iofw_regentry {
    const char *name;
    iofw_open_f *open;
    iofw_close_f *close;
    iofw_read_f *read;
    iofw_write_f *write;
    iofw_fstat_f *fstat;
    iofw_isatty_f *isatty;
    void *handle;
    SLIST_ENTRY(iofw_regentry) entries;
};

SLIST_HEAD(iofw_registry_list, iofw_regentry);
extern struct iofw_registry_list iofw_registry;




#endif//IOFW_TYPES_H
