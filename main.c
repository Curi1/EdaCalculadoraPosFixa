#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "pilha.h"



double avaliarExpressaoPosfixada(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            empilhar(&pilha, atof(token));
        } else {
            double operando1 = 0.0, operando2 = 0.0, resultado = 0.0;

            // Verificar se é uma operação unária
            if (strcmp(token, "log") == 0 || strcmp(token, "sin") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0) {
                operando1 = desempilhar(&pilha);

                if (strcmp(token, "sin") == 0) {
                    resultado = sin(operando1);
                } else if (strcmp(token, "cos") == 0) {
                    resultado = cos(operando1);
                } else if (strcmp(token, "tan") == 0) {
                    resultado = tan(operando1);
                } else if (strcmp(token, "log") == 0) {
                    resultado = log10(operando1);
                }
            } else {
                // Para operações binárias
                operando2 = desempilhar(&pilha);
                operando1 = desempilhar(&pilha);

                if (strcmp(token, "+") == 0) {
                    resultado = operando1 + operando2;
                } else if (strcmp(token, "-") == 0) {
                    resultado = operando1 - operando2;
                } else if (strcmp(token, "*") == 0) {
                    resultado = operando1 * operando2;
                } else if (strcmp(token, "/") == 0) {
                    resultado = operando1 / operando2;
                } else if (strcmp(token, "^") == 0) {
                    resultado = pow(operando1, operando2);
                }
            }

            empilhar(&pilha, resultado);
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

int main() {
    char expressao[] = "3 4 + 5 *";  // Exemplo de expressão pós-fixa
    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Resultado: %f\n", resultado);

    return 0;
}
