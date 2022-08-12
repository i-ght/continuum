#include "continuum.h"

static void* free_data(const size_t space)
{
#define AMOUNT_AVAIL 10000

    if (space > AMOUNT_AVAIL) {
        exit(EXIT_FAILURE);
    }
    static char free_data[AMOUNT_AVAIL] = {0};
    return (void*)free_data;
}

int main(void)
{
    struct Continuum continuum = {0};

    continuum_construct(&continuum, realloc, free);

    for (int i = 0; i < 999; i++) {
        if (-1 == 
            continuum_write_cstr(
                &continuum,
                "abc"
            )
        ) {
            return EXIT_FAILURE;
        }
    }

    static const char expected[] = "abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc";

    char* tmp = NULL;

    if (-1 ==
        continuum_copy_writ_data(
            &continuum,
            &tmp,
            free_data
        )
    ) {
        return EXIT_FAILURE;
    }

    bool ok = 0 == memcmp(
        expected,
        tmp,
        continuum_writ(&continuum)
    );

    if (!ok) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}