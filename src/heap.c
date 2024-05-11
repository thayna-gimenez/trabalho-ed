#include <stdio.h>
#include <stdlib.h>

#include "../include/libkdtree.h"
#include "../include/libheap.h"

int trocar(tVizinho *a, tVizinho *b){
    tVizinho aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

int pai(int node) {
    return ( - 1) / 2;
}

int filho_esq(int node){
    return (node * 2) + 1;
}

int filho_dir(int node){
    return (node * 2) + 2;
}

void construir_heap(tHeap *heap, int n){
    heap->vetor = (tVizinho *) malloc(n * sizeof(tVizinho));

    heap->tam = 0;
    heap->max = n;  
}

void constroi_heap_vetor(tHeap *heap){
    int ultimo_pai = pai(heap->tam - 1);

    for (int i = ultimo_pai; i >= 0; i--){
        desce_max(heap, i, heap->tam);
    }
}

// calcula a distância em outro lugar
void inserir_heap(tHeap *heap, void *reg, double distancia){
    //inserir_heap(tHeap *heap, tMunicipio *reg, double distancia)

    // alocando cada valor nos buckets do vetor
    if (heap->tam < heap->max){
        heap->vetor[heap->tam].reg = reg; //cidade
        heap->vetor[heap->tam].distancia = distancia;
        
        sobe_max(heap, heap->tam);

        heap->tam += 1;

    }
    
}

void desce_max(tHeap *heap, int no, int tam_heap){
    int maior = no;
    int esq = filho_esq(no);
    int dir = filho_dir(no);

    // na heap normal compara os numeros, aqui compara as distancias
    if (esq < tam_heap && heap->vetor[esq].distancia > heap->vetor[maior].distancia){
        maior = esq;
    }

    if (dir < tam_heap && heap->vetor[dir].distancia > heap->vetor[maior].distancia){
        maior = dir;
    }

    if (maior != no){
        trocar(&(heap->vetor[no]), &(heap->vetor[maior]));
        desce_max(heap, maior, tam_heap);
    }
}

void sobe_max(tHeap *heap, int no){
    int pai_no = pai(no);

    while(no > 0 && heap->vetor[no].distancia > heap->vetor[pai_no].distancia){
        trocar(&(heap->vetor[no]), &(heap->vetor[pai_no]));

        no = pai_no;
        pai_no = pai(no);
    }
}

int altera_prioridade(tHeap *heap, int no, double distancia, void * reg){

    // if (heap->vetor[no].distancia < distancia){
    //     heap->vetor[no].reg = reg;
    //     sobe_max(heap, no);
    // }

    if (heap->vetor[no].distancia > distancia){
        heap->vetor[no].reg = reg;
        heap->vetor[no].distancia = distancia;
        desce_max(heap, no, heap->tam);
    }

    return EXIT_SUCCESS;
}

void heapsort(tHeap *heap){
    constroi_heap_vetor(heap);
    
    for (int i = heap->tam - 1; i > 0; i--){
        trocar(&(heap->vetor[i]), &(heap->vetor[0]));
        desce_max(heap, 0, i);
    }
}

void imprimir_heap(tHeap *heap){
    for (int i = 0; i < heap->tam; i++){
        printf("\nCódigo IBGE: %s\n", heap->vetor[i].reg->codigo_ibge);
        printf("Cidade: %s\n", heap->vetor[i].reg->nome);
    }
}

