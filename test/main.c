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
#include "../include/libheap.h"

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
    double retorno;
    if (nivel % 2 == 0){
        retorno = ((tMunicipio *) reg1)->latitude - ((tMunicipio *) reg2)->latitude;
    }
    else {
        retorno = ((tMunicipio *) reg1)->longitude - ((tMunicipio *) reg2)->longitude;
    }

    return retorno;
}

int main(){
    tHash hash;
    tArv *arv = (tArv *) malloc(sizeof(tArv));
    tHeap *heap = (tHeap *) malloc(sizeof(tHeap));
    //tHeap heap;
    int opcao, n;
    char codigo[10];

    inicializar_hash(&hash, 15877, get_key);
    inicializar_kdtree(arv, cmp);

    FILE *arquivo = fopen("municipios.json", "r");
    leitor(arquivo, &hash, arv);

    printf("1 - Consulta de cidade por código IBGE\n");
    printf("2 - Consulta de n cidades mais próximas pelo código IBGE\n");
    printf("Digite a opção desejada: ");

    scanf("%d", &opcao);

    if (opcao == 1){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s", codigo);

        tMunicipio *cidade = buscar_hash(hash, codigo);
        
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

    else if (opcao == 2){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s", codigo);

        printf("\nInsira a quantidade de vizinhos a serem procurados: ");
        scanf("%d", &n);

        construir_heap(heap, n);

        tMunicipio *cidade = buscar_hash(hash, codigo);
        buscar_vizinho(arv, arv->raiz, heap, cidade, 0, n);

        heapsort(heap);
        imprimir_heap(heap);
    }

    else {
        printf("tchau");
    }
    
}