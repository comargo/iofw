#ifndef IOFW_SLOTS_H
#define IOFW_SLOTS_H

#include <stdint.h>
#include "iofw_types.h"

#define MAX_OPEN_FILES 20

#define INVALID_HANDLE ((void*)UINTPTR_MAX)
#define SYSTEM_HANDLE (INVALID_HANDLE-1)
struct iofw_file {
    void *handle;
    iofw_close_f *close;
    iofw_read_f *read;
    iofw_write_f *write;
    iofw_fstat_f *fstat;
    iofw_isatty_f *isatty;
};

extern struct iofw_file openfiles[MAX_OPEN_FILES];

int iofw_newslot();
int iofw_findslot(void *handle);


#endif//IOFW_SLOTS_H
