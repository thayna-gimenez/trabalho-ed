#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// criando a hash
typedef struct {
    uintptr_t *tabela;
    int tam;
    int max;
    uintptr_t deletado;
    char * (*get_key)(void *);
} tHash;

