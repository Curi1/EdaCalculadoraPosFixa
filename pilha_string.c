#include "pilha_string.h"
#include <string.h>
#include <stdio.h>

void inicializarString(PilhaString *pilha) {
    pilha->topo = NULL;
}

void empilharString(PilhaString *pilha, char* valor) {
    NoString *novoNo = malloc(sizeof(NoString));
    novoNo->dado = strdup(valor); // Duplica a string
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

char* desempilharString(PilhaString *pilha) {
    if (pilha->topo == NULL) {
        printf("Erro: Pilha vazia\n");
        return NULL;
    }
    NoString *temp = pilha->topo;
    char* valor = temp->dado;
    pilha->topo = temp->proximo;
    free(temp);
    return valor;
}


