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

char *get_key_nome(void *reg){
    return (*((tMunicipio *)reg)).nome;
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
    tHash hash_cod;
    tHash hash_nome;
    tArv *arv = (tArv *) malloc(sizeof(tArv));
    tHeap *heap = (tHeap *) malloc(sizeof(tHeap));
    //tHeap heap;
    int opcao, n;
    char codigo[10], nome_cidade[50];

    inicializar_hash(&hash_cod, 15877, get_key);
    inicializar_hash(&hash_nome, 15877, get_key_nome);
    inicializar_kdtree(arv, cmp);

    FILE *arquivo = fopen("municipios.json", "r");
    leitor(arquivo, &hash_cod, &hash_nome, arv);

    printf("1 - Consulta de cidade por código IBGE\n");
    printf("2 - Consulta de n cidades mais próximas pelo código IBGE\n");
    printf("3 - Consulta de n cidades mais próximas pelo nome da cidade\n");
    printf("4 - Sair\n");
    printf("Digite a opção desejada: ");

    scanf("%d", &opcao);

    if (opcao == 1){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s", codigo);
        printf("\n");

        if (codigo <= 0){
            printf("Código inválido.\n");
        }

        tMunicipio *cidade = buscar_hash(hash_cod, codigo);
        
        printf("Código IBGE: %s\n", cidade->codigo_ibge);
        printf("Cidade: %s\n", cidade->nome);
        printf("Latitude: %f\n", cidade->latitude);
        printf("Longitude: %f\n", cidade->longitude);
        printf("Capital: %d\n", cidade->capital);
        printf("Código da UF: %d\n", cidade->codigo_uf);
        printf("Código SIAFI: %d\n", cidade->siafi_id);
        printf("DDD: %d\n", cidade->ddd);
        printf("Fuso horário: %s\n", cidade->fuso_horario);

        apagar_hash(&hash_cod);
    }

    else if (opcao == 2){
        printf("\nInsira o código da cidade a ser consultada: ");
        scanf("%s", codigo);

        printf("Insira a quantidade de vizinhos a serem procurados: ");
        scanf("%d", &n);

        if (codigo <= 0){
            printf("Código inválido.");
        }

        construir_heap(heap, n);

        tMunicipio *cidade = buscar_hash(hash_cod, codigo);
        buscar_vizinho(arv, arv->raiz, heap, cidade, 0, n);

        heapsort(heap);
        imprimir_heap(heap);
        printf("\n");

        apagar_heap(heap);
        apagar_hash(&hash_cod);
        apagar_kdtree(arv);
    }

    else if (opcao == 3){
        printf("\nInsira o nome da cidade a ser consultada: ");
        scanf(" %[^\n]", nome_cidade);

        printf("Insira a quantidade de vizinhos a serem procurados: ");
        scanf("%d", &n);

        construir_heap(heap, n);

        tMunicipio **cidades = buscar_hash_nomes(hash_nome, nome_cidade);

        if (cidades[0] != NULL){ // existe 
            if (cidades[1] != NULL){
                printf("\nExiste mais de uma cidade com esse nome!");
                printf("\n");

                int i;

                for (i = 0; cidades[i] != NULL; i++){
                    printf("\nCódigo IBGE | Cidade | Fuso horário");
                    printf("\n%s | %s | %s", cidades[i]->codigo_ibge, cidades[i]->nome, cidades[i]->fuso_horario);
                }

                printf("\nInsira o código IBGE da cidade escolhida: ");
                scanf("%s", codigo);

                tMunicipio *cidade = buscar_hash(hash_cod, codigo);
                buscar_vizinho(arv, arv->raiz, heap, cidade, 0, n);
                heapsort(heap);
                imprimir_heap(heap);
                printf("\n");
            }

            else {
                tMunicipio *cidade_nome = buscar_hash(hash_nome, cidades[0]->nome);
                buscar_vizinho(arv, arv->raiz, heap, cidades[0], 0, n);
                heapsort(heap);
                imprimir_heap(heap);
                printf("\n");
            }
        }

        else {
            printf("\nCidade inválida.");
            printf("\n");
        }

        apagar_heap(heap);
        apagar_hash(&hash_cod);
        apagar_hash(&hash_nome);
        apagar_kdtree(arv);
    }

    else if (opcao == 4){
        printf("");
    }

    else {
        printf("\nOpção inválida.\n");
        printf("\n");
    }

}