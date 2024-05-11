#ifndef __LIBHEAP__
#define __LIBHEAP__

#include <stdlib.h>

#include "libstruct.h"

typedef struct {
    tMunicipio *reg; // bucket com todas as informações da cidade
    double distancia; // distancia em relação ao nó comparado
} tVizinho;

typedef struct {
    tVizinho *vetor; // vetor com buckets do tipo tVizinho (com o bucket do tipo TMunicipio e a distancia)
    int tam;
    int max;
}tHeap;

int pai(int node);
int filho_esq(int node);
int filho_dir(int node);
void construir_heap(tHeap *heap, int n);
void constroi_heap_vetor(tHeap *heap);
void inserir_heap(tHeap *heap, void *reg, double distancia);
void desce_max(tHeap *heap, int no, int tam_heap);
void sobe_max(tHeap *heap, int no);
int altera_prioridade(tHeap *heap, int no, double distancia, void * reg);
void heapsort(tHeap *heap);
void imprimir_heap(tHeap *heap);


#endif