#ifndef _CONTINUUMH_
#define _CONTINUUMH_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CONTINUUM_MAX_BUFFER_SPACE
#define CONTINUUM_MAX_BUFFER_SPACE (size_t)1134903170 /* 1 gigabyte ~ 1,134 megabytes */
#endif

#ifndef CONTINUUM_DEFAULT_BUFFER_SIZE
#define CONTINUUM_DEFAULT_BUFFER_SIZE 144
#endif

typedef void* (*MemoryAllocate)(const size_t size);

typedef void* (*MemoryReallocate)(
    void* address,
    const size_t size
);

typedef void (*MemoryFree)(void* address);

struct Continuum 
{
    size_t read;
    size_t writ;
    size_t space;
    char* spacetime;
    MemoryReallocate mem_realloc;
    MemoryFree mem_free;

};

int continuum_realloc(
    struct Continuum* continuum,
    const size_t new_space
);

void continuum_construct(
    struct Continuum* continuum,
    const MemoryReallocate mem_realloc,
    const MemoryFree mem_free
);

void continuum_destruct(
    struct Continuum* continuum
);

int continuum_write(
    struct Continuum* continuum,
    const char* data,
    const size_t required_space
);

int continuum_write_cstr(
    struct Continuum* continuum,
    const char c_str[]
);

size_t continuum_writ(
    const struct Continuum* continuum
);

int continuum_set_write_pos(
    struct Continuum* continuum,
    const size_t write_pos
);

int continuum_copy_writ_data(
    const struct Continuum* continuum,
    char** output,
    const MemoryAllocate mem_alloc
);

#endif