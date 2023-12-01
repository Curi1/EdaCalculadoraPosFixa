#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    No *temp = pilha->topo;
    double valor = temp->dado;
    pilha->topo = temp->proximo;
    free(temp);
    return valor;
}

