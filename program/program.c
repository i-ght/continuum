#include "continuum.h"

int main(void)
{
    struct Continuum continuum = {0};

    continuum_construct(&continuum, realloc, free);

    for (int i = 0; i < 999; i++) {
        if (-1 == 
            continuum_write_cstr(
                &continuum,
                "hello world"
            )
        ) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}