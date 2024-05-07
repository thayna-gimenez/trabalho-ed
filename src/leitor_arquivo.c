#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libparser.h"

#define TAM_LINHA 1024

void parser(FILE *arquivo){
    char linha[TAM_LINHA];

    while(fgets(linha, TAM_LINHA, arquivo) != NULL){

        char *inicio = strpbrk(linha, ":");
        
    }

}

int main(){
    FILE *arquivo = fopen("municipios.json", "r");

    parser(arquivo);
}
