#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/libhash.h"

#define TAM_HASH 15877 // numero primo
#define SEED 0x12345678

// cnstruindo a hash
void inicializar_hash(tHash *hash, int nbuckets, char * (*get_key)(void *)){
    hash->tabela = calloc(sizeof(void *), nbuckets);

    // se nbuckets = 0;
    if (hash->tabela == NULL)
        return EXIT_FAILURE;

    hash->max = nbuckets;
    hash->tam = 0;
    hash->deletado = (uintptr_t)&(hash->tam);
    hash->get_key = get_key;

    return EXIT_SUCCESS;
}

// função hash
// soma de todos os caracteres da chave
uint32_t hashf(const char* str, uint32_t h){
    /* One-byte-at-a-time Murmur hash 
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

int mod_chave(uint32_t chave, int tam_hash){
    return chave % tam_hash;
}

// hashing duplo
int hashing_duplo(const char *chave, int tentativas, int tam_hash){
    int hash1 = mod_chave(hashf(chave, SEED), TAM_HASH); // posição inicial do elemento
    int hash2 = mod_chave(hashf(chave, SEED), TAM_HASH); // calcular os deslocamentos em relação à posição inicial (no caso de uma colisão)
    
    return (hash1 + tentativas * hash2) % tam_hash;
}