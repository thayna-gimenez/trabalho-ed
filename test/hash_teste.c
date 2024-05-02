#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/libhash.h"

// criando hash específica
typedef struct {
    char codigo_ibge[10];
    char nome[30];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[35];
} tMunicipio;


// definindo que a chave do usuário é codigo_ibge
char *get_key(void *reg){
    return (*((tMunicipio *)reg)).codigo_ibge;
}

void teste_constroi(){
    tHash hash;
    int nbuckets = 10;
    
    assert(inicializar_hash(&hash, nbuckets, get_key) == EXIT_SUCCESS); // inicializando a hash e mandando codigo_ibge como chave
}

int main(){
    teste_constroi();
}