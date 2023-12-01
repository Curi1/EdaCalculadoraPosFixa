#ifndef PILHA_H
#define PILHA_H

typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

void inicializar(Pilha *pilha);
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);

#endif


