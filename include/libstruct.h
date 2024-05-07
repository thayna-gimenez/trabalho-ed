#ifndef __LIBSTRUCT__
#define __LIBSTRUCT__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

#endif