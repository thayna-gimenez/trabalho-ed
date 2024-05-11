#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libstruct.h"
#include "../include/libparser.h"
#include "../include/libhash.h"
#include "../include/libkdtree.h"

#define TAM_LINHA 1024

void substituir_virgula(char *inicio_linha){
    char *final = strpbrk(inicio_linha, ",");

            // tirando a vírgula do final da linha
            if (final != NULL){
                *final = '\0';
            }
}

void leitor(FILE *arquivo, tHash *hash, tArv *arv){
    char linha[TAM_LINHA];
    tMunicipio *cidade;

    while (fgets(linha, TAM_LINHA, arquivo) != NULL){

        // colocando os valores nas variáveis do bucket

        if (strstr(linha, "codigo_ibge") != NULL){
            aloca_cidade(&cidade);

            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            strcpy(cidade->codigo_ibge, inicio);

        }

        else if (strstr(linha, "nome") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            strcpy(cidade->nome, inicio);

        }

        else if (strstr(linha, "latitude") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->latitude = atof(inicio);

        }

        else if (strstr(linha, "longitude") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->longitude = atof(inicio);

        }

        else if (strstr(linha, "capital") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->capital = atoi(inicio);

        }

        else if (strstr(linha, "codigo_uf") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->codigo_uf = atoi(inicio);

        }

        else if (strstr(linha, "siafi_id") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->siafi_id = atoi(inicio);

        }

        else if (strstr(linha, "ddd") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            cidade->ddd = atoi(inicio);

        }

        else if (strstr(linha, "fuso_horario") != NULL){
            char *inicio = strpbrk(linha, ":");
            inicio += 2;

            substituir_virgula(inicio);

            strcpy(cidade->fuso_horario, inicio);

            inserir_hash(hash, cidade);
            inserir_kdtree(arv, cidade);
            
        }
        
    }


}
