#ifndef PILHA_STRING_H
#define PILHA_STRING_H

#include <stdlib.h>
#include <string.h>

typedef struct NoString {
    char* dado;
    struct NoString *proximo;
} NoString;

typedef struct {
    NoString *topo;
} PilhaString;

void inicializarString(PilhaString *pilha);
void empilharString(PilhaString *pilha, char* valor);
char* desempilharString(PilhaString *pilha);

#endif

