#include "iofw_types.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <reent.h>

#define declare_ref(fn) static void *ref##fn = &fn

declare_ref(_open_r);
declare_ref(_close_r);
declare_ref(_read_r);
declare_ref(_write_r);
declare_ref(_fstat_r);
declare_ref(_isatty_r);

#define make_ref(fn) ref##fn = &fn;
__attribute__((used)) void reference()
{
    make_ref(_open_r);
    make_ref(_close_r);
    make_ref(_read_r);
    make_ref(_write_r);
    make_ref(_fstat_r);
    make_ref(_isatty_r);
}

struct iofw_registry_list iofw_registry = SLIST_HEAD_INITIALIZER(iofw_registry);

void iofw_add_registry(const struct iofw_regentry *entry)
{
    struct iofw_regentry *newEntry = calloc(1, sizeof(struct iofw_regentry));
    memcpy(newEntry, entry, sizeof(*entry));
    SLIST_INSERT_HEAD(&iofw_registry, newEntry, entries);
}

