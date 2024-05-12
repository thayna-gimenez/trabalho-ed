#ifndef __LIBKDTREE__
#define __LIBKDTREE__

#include <stdint.h>

#include "libheap.h"

//criando nó genérico da árvore
typedef struct _tNode{
    void *reg; // cidade
    struct _tNode *esq;
    struct _tNode *dir;
} tNode;

// criando árvore genérica
typedef struct _kdtree {
    tNode *raiz;
    double (*cmp) (void *, void *, int);
    //double (*distancia) (void *, void *);
} tArv;

double distancia(void *reg1, void *reg2);
void inicializar_kdtree(tArv *arv, double (*cmp)(void *, void*, int));
void inserir_node(tArv *arv, tNode **node, void *reg, int nivel);
void inserir_kdtree(tArv *arv, void *reg);
void buscar_vizinho(tArv *arv, tNode *node, tHeap *heap, void *reg, int nivel, int n);
void apagar_kdtree(tArv *arv);

#endif