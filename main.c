#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Estrutura da pilha
typedef struct No {
    char *dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

// Inicializa a pilha
void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

// Empilha um valor
void empilhar(Pilha *pilha, char *valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = strdup(valor);
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Desempilha um valor
char* desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    No *temp = pilha->topo;
    char *valor = temp->dado;
    pilha->topo = temp->proximo;
    free(temp);
    return valor;
}

// Avalia a expressão pós-fixa
double avaliarExpressaoPosfixada(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, token);
        } else {
            double operando2 = atof(desempilhar(&pilha));
            double operando1 = atof(desempilhar(&pilha));
            double resultado;

            switch (token[0]) {
                case '+': resultado = operando1 + operando2; break;
                case '-': resultado = operando1 - operando2; break;
                case '*': resultado = operando1 * operando2; break;
                case '/': resultado = operando1 / operando2; break;
            }

            char *resStr = (char *)malloc(20);
            sprintf(resStr, "%f", resultado);
            empilhar(&pilha, resStr);
            free(resStr);
        }
        token = strtok(NULL, " ");
    }

    return atof(desempilhar(&pilha));
}

// Converte expressão pós-fixa para pré-fixa
char* converterPosFixaParaPreFixa(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, token);
        } else {
            char *operando2 = desempilhar(&pilha);
            char *operando1 = desempilhar(&pilha);

            int size = strlen(operando1) + strlen(operando2) + 6;
            char *novaExpressao = (char *)malloc(size);
            snprintf(novaExpressao, size, "(%s %c %s)", operando1, token[0], operando2);

            free(operando1);
            free(operando2);

            empilhar(&pilha, novaExpressao);
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

int main() {
    char expressao[] = "12 4 + 5 *"; // Exemplo de expressão pós-fixa
    char *expressaoPreFixa = converterPosFixaParaPreFixa(expressao);
    printf("Expressão Pré-fixa: %s\n", expressaoPreFixa);

    char expressaoParaCalcular[] = "12 4 + 5 *"; // Exemplo de expressão pós-fixa para calcular
    double resultado = avaliarExpressaoPosfixada(expressaoParaCalcular);
    printf("Resultado: %f\n", resultado);

    free(expressaoPreFixa);
    return 0;
}
