#include "continuum.h"

enum {OK=0,ERR=-1};
enum {ZERO=0};
#define PHI 1.618033989

static int realloc_buffer(
    const size_t new_space,
    char** buffer,
    const MemoryReallocate mem_realloc)
{
    if (new_space > CONTINUUM_MAX_BUFFER_SPACE) {
        return ERR;
    }

    char* tmp = 
        (char*)mem_realloc(
            *buffer,
            new_space
        );
    if (NULL == tmp) {
        return ERR;
    }
    
    *buffer = tmp;
    return OK;

}

void continuum_construct(
    struct Continuum* continuum,
    const MemoryReallocate mem_realloc,
    const MemoryFree mem_free)
{
    continuum->mem_realloc = mem_realloc;
    continuum->mem_free = mem_free;
    continuum->spacetime =  NULL;
    continuum->writ = ZERO;
    continuum->read = ZERO;
    continuum->space = ZERO;
}


int continuum_realloc_buffer(
    struct Continuum* continuum,
    const size_t new_space)
{
    if (-1 == 
        realloc_buffer(
            new_space,
            &continuum->spacetime,
            continuum->mem_realloc
        )
    ) {
        return ERR;
    }

    continuum->space = new_space;
    
    return OK;
}

void continuum_destruct(
    struct Continuum* continuum)
{
    if (NULL != continuum->spacetime && NULL != continuum->mem_free) {
        continuum->mem_free(continuum->spacetime);
        continuum->spacetime = NULL;
        continuum->mem_free = NULL;
    }

    continuum->writ = ZERO;
    continuum->space = ZERO;    
}

ptrdiff_t continuum_read(struct Continuum* continuum, char* buffer, const ptrdiff_t buffer_i, const size_t buffer_space)
{
    const void* zero_point = &continuum->spacetime[0];
    return ERR;
}

int continuum_write(
    struct Continuum* continuum,
    const char* data,
    const size_t required_space)
{
    if (NULL == data) {
        return ERR;
    }

    if (ZERO == required_space) {
        return ERR;
    }

    if (required_space > CONTINUUM_MAX_BUFFER_SPACE) {
        return ERR;
    }

    ptrdiff_t remaining_space =
        continuum->space - continuum->writ;

    while (remaining_space < required_space) {

        /* acquisition more space */
        if (ERR ==
            continuum_realloc_buffer(
                continuum,
                (continuum->space <= CONTINUUM_DEFAULT_BUFFER_SIZE ? CONTINUUM_DEFAULT_BUFFER_SIZE : continuum->space) * PHI
            )
        ) {
            return ERR;
        }

        remaining_space =
            continuum->space - continuum->writ;
    }

    const ptrdiff_t i = continuum->writ;
    if (i < 0 || i > continuum->writ) {
        return ERR;
    }
    
    void* time_slice = (void*)&continuum->spacetime[i];
    const void* _ =
        memmove(
            time_slice,
            data,
            required_space
        );

    continuum->writ += required_space;

    return OK;
}

int continuum_write_cstr(
    struct Continuum* continuum,
    const char c_str[])
{
    return
        continuum_write(
            continuum,
            c_str,
            strlen(c_str)
        );
}

size_t continuum_writ(
    const struct Continuum* continuum)
{
    return continuum->writ;
}

int continuum_set_write_pos(
    struct Continuum* continuum,
    const size_t write_pos)
{
    if (write_pos >= continuum->space) {
        return ERR;
    }
    continuum->writ = write_pos;

    return OK;
}

int continuum_copy_writ_data(
    const struct Continuum* continuum,
    char** output,
    const MemoryAllocate mem_alloc)
{
    char* tmp = (char*)mem_alloc(continuum->writ + 1);

    const void* _ =
        memmove(
            tmp,
            continuum->spacetime,
            continuum->writ
        );

    *output = tmp;

    return OK;
}