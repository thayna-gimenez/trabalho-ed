#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/libkdtree.h"
#include "../include/libstruct.h"
#include "../include/libheap.h"

double distancia(void *reg1, void *reg2){
    double x = pow(((tMunicipio *) reg2)->latitude - ((tMunicipio *) reg1)->latitude, 2);
    double y = pow(((tMunicipio *) reg2)->longitude - ((tMunicipio *) reg1)->longitude, 2);

    return  x + y;
}

// criando a árvore
void inicializar_kdtree(tArv *arv, double (*cmp)(void *, void*, int)){
    arv->raiz = NULL;
    arv->cmp = cmp;
}

// vai comparando nós até adicionar o reg, a partir da raíz da árvore
void  inserir_node(tArv *arv, tNode **node, void *reg, int nivel){
    if(*node == NULL){ // se não existir nó raíz, cria um 
        *node = malloc(sizeof(tNode));
        (*node)->reg = reg; // cidade
        (*node)->esq = NULL;
        (*node)->dir = NULL;
    }

    else if (arv->cmp((*node)->reg, reg, nivel) > 0) { // vai para a esquerda
        inserir_node(arv, &((*node)->esq), reg, ++nivel); }

    else { // vai para a direita
        inserir_node(arv, &((*node)->dir), reg, ++nivel); }
}

// adiciona a cidade na árvore
void inserir_kdtree(tArv *arv, void *reg){
    inserir_node(arv, &arv->raiz, reg, 0);
}

void buscar_vizinho(tArv *arv, tNode *node, tHeap *heap, void *reg, int nivel, int n){

    if (node != NULL){ // não existe o nó
        tNode *prox_node;
        tNode *outro_node;

        double dist = distancia(node->reg, reg);

        if (heap->tam < n && dist > 0){
            inserir_heap(heap, node->reg, dist);
        }

        else if (dist < heap->vetor[0].distancia && dist > 0){
        
            altera_prioridade(heap, 0, dist, node->reg);
        }

        buscar_vizinho(arv, node->esq, heap, reg, ++nivel, n);
        buscar_vizinho(arv, node->dir, heap, reg, ++nivel, n);
    }
}

void apagar_kdtree(tArv *arv){
    free(arv->raiz);
    free(arv);
}
