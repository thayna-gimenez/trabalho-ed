#ifndef __LIBABB__
#define __LIBABB__

#include <stdint.h>

//criando nó genérico da árvore
typedef struct _tNode{
    void *reg;
    struct _tNode *esq;
    struct _tNode *dir;
} tNode;

// criando árvore genérica
typedef struct _abb {
    tNode *raiz;
    double (*cmp) (void *, void *, int);
} tArv;

void inicializar_abb(tArv *arv, double (*cmp)(void *, void*, int));
int inserir_node(tArv *arv, tNode **node, void *reg, int nivel);
int inserir_abb(tArv *arv, void *reg);
void * buscar_abb(tArv * arv, void * reg);

#endif