#include <stdint.h>
#include <stddef.h>

typedef struct reflector {
    uint64_t values[UINT64_MAX]
} reflector_t;

reflector_t *create_reflector(void);

