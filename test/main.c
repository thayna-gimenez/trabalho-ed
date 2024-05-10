#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "../include/libhash.h"
#include "../include/libstruct.h"
#include "../include/libparser.h"
#include "../include/libkdtree.h"

// definindo que a chave do usuário é codigo_ibge
char *get_key(void *reg){
    return (*((tMunicipio *)reg)).codigo_ibge;
}

// alocando um bucket cidade sem determinar os valores de seus atributos
void aloca_cidade(tMunicipio **cidade){
    *cidade = (tMunicipio*) malloc(sizeof(tMunicipio));
}

// função para comparar na hora de inserir na kdtree
// para ver se o nó vai para a esquerda ou para a direita
double cmp(void *reg1, void *reg2, int nivel){
    if (nivel % 2 == 0)
        return ((tMunicipio *) reg1)->latitude - ((tMunicipio *) reg2)->latitude;
    else
        return ((tMunicipio *) reg1)->longitude - ((tMunicipio *) reg2)->longitude;
}

double distancia(void *reg1, void *reg2){
    double x = pow(((tMunicipio *) reg2)->latitude - ((tMunicipio *) reg1)->latitude, 2);
    double y = pow(((tMunicipio *) reg2)->longitude - ((tMunicipio *) reg1)->longitude, 2);

    return  x + y;
}

int main(){
    tHash hash;
    tArv arv;
    int opcao;
    char codigo[10];

    inicializar_hash(&hash, 15877, get_key);
    inicializar_kdtree(&arv, cmp, distancia);

    FILE *arquivo = fopen("municipios.json", "r");
    leitor(arquivo, &hash, &arv);

    printf("1 - Consulta de cidade por código IBGE\n");
    printf("Digite a opção desejada: ");

    scanf("%d", &opcao);

    if (opcao == 1){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s", codigo);

        tMunicipio *cidade_hash = buscar_hash(hash, codigo);
        tMunicipio *cidade = buscar_kdtree(&arv, cidade_hash);
        
        printf("Código IBGE: %s\n", cidade->codigo_ibge);
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