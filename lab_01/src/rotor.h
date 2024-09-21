#include <stdint.h>
#include <stddef.h>

typedef struct rotor {
    uint64_t values[UINT64_MAX];
    size_t position;
} rotor_t;

uint64_t get_forward(rotor_t *rotor, uint64_t symbol);

uint64_t get_reverse(rotor_t *rotor, uint64_t symbol);

void rotate(rotor_t *rotor);

rotor_t *create_rotor(void);

