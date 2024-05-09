#include <stdio.h>
#include <stdlib.h>
#include "../include/libabb.h"
#include "../include/libstruct.h"

// criando a árvore
void inicializar_abb(tArv *arv, double (*cmp)(void *, void*, int)){
    arv->raiz = NULL;
    arv->cmp = cmp;
}

// vai comparando nós até adicionar o reg, a partir da raíz da árvore
int inserir_node(tArv *arv, tNode **node, void *reg, int nivel){
    if(*node == NULL){ // se não existir nó raíz, cria um 
        *node = malloc(sizeof(tNode));
        (*node)->reg = reg;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
    }

    else if (arv->cmp((*node)->reg, reg, nivel) > 0) { // vai para a esquerda
        inserir_node(arv, &((*node)->esq), reg, ++nivel); }

    else { // vai para a direita
        inserir_node(arv, &((*node)->dir), reg, ++nivel); }
}

// adiciona a cidade na árvore
int inserir_abb(tArv *arv, void *reg){
    return inserir_node(arv, &arv->raiz, reg, 0);
}

void * buscar_node(tArv *arv, tNode *node, void *reg, int nivel){
    tNode *retorno;

    if (node == NULL){ // não existe o nó
        retorno = NULL;
    }

    else if (arv->cmp(node->reg, reg, nivel) > 0) { // vai para a esquerda
        retorno = buscar_node(arv, node->esq, reg, ++nivel);
    }
    else if (arv->cmp(node->reg, reg, nivel) < 0){ // vai para a direita
        retorno = buscar_node(arv, node->dir, reg, ++nivel);
    }
    else {
        retorno = node->reg;
    }

    return retorno;
}

void * buscar_abb(tArv * arv, void * reg){
    return buscar_node(arv, arv->raiz, reg, 0);
}
