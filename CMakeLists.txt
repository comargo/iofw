cmake_minimum_required(VERSION 2.8)
project(iofw)
set(iofw_sources
        src/iofw_open.c
        src/iofw_close.c
        src/iofw_write.c
        src/iofw_read.c
        src/iofw_fstat.c
        src/iofw_isatty.c
        src/iofw_registry.c
        src/iofw_slots.c
)

set(iofw_headers
        inc/iofw_types.h
        inc/iofw_registry.h
        inc/iofw_slots.h
)

add_library(iofw STATIC ${iofw_sources} ${iofw_headers})

target_include_directories(iofw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
