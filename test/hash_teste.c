// casos de teste e funções específicas da hash

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/libhash.h"
#include "../include/libstruct.h"
#include "../include/libparser.h"

// definindo que a chave do usuário é codigo_ibge
char *get_key(void *reg){
    return (*((tMunicipio *)reg)).codigo_ibge;
}

// alocando um bucket cidade sem determinar os valores de seus atributos
void aloca_cidade(tMunicipio **cidade){
    *cidade = (tMunicipio*) malloc(sizeof(tMunicipio));
}

int main(){
    tHash hash;
    int opcao;
    char codigo[10];

    inicializar_hash(&hash, 15877, get_key);

    FILE *arquivo = fopen("municipios.json", "r");
    leitor(arquivo, &hash);

    printf("1 - Consulta de cidade por código IBGE\n");
    printf("Digite a opção desejada: ");

    scanf("%d", &opcao);

    if (opcao == 1){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s\n", codigo);

        tMunicipio *cidade = buscar_hash(hash, codigo);
        printf("Cidade: %s\n", cidade->nome);
        printf("Latitude: %f\n", cidade->latitude);
        printf("Longitude: %f\n", cidade->longitude);
        printf("Capital: %d\n", cidade->capital);
        printf("Código da UF: %d\n", cidade->codigo_uf);
        printf("Código SIAFI: %d\n", cidade->siafi_id);
        printf("DDD: %d\n", cidade->ddd);
        printf("Fuso horário: %s\n", cidade->fuso_horario);
    }
    
}