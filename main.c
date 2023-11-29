#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "pilha.h"
#include "pilha_string.h"



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


int ehUnario(char* operador) {
    return strcmp(operador, "log") == 0 ||
           strcmp(operador, "sen") == 0 ||
           strcmp(operador, "cos") == 0 ||
           strcmp(operador, "tan") == 0;
}

char* concatenarParaPreFixa(char* operador, char* operando1, char* operando2) {
    int tamanho;
    char* resultado;

    if (ehUnario(operador)) {
        tamanho = strlen(operador) + strlen(operando1) + 3;
        resultado = (char*) malloc(tamanho);
        snprintf(resultado, tamanho, "%s(%s)", operador, operando1);
    } else {
        int precisaParenteses1 = strchr(operando1, ' ') != NULL;
        int precisaParenteses2 = operando2 && strchr(operando2, ' ') != NULL;
        tamanho = strlen(operador) + strlen(operando1) + (operando2 ? strlen(operando2) : 0) + 4 + (precisaParenteses1 ? 2 : 0) + (precisaParenteses2 ? 2 : 0);
        resultado = (char*) malloc(tamanho);
        snprintf(resultado, tamanho, "%s%s%s %s %s%s%s",
                 precisaParenteses1 ? "(" : "", operando1, precisaParenteses1 ? ")" : "",
                 operador,
                 precisaParenteses2 ? "(" : "", operando2, precisaParenteses2 ? ")" : "");
    }

    return resultado;
}

char* converterPosFixaParaPreFixa(char *expressao) {
    PilhaString pilha;
    inicializarString(&pilha);

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])) || token[0] == '.') {
            empilharString(&pilha, token);
        } else {
            char *operando2 = ehUnario(token) ? NULL : desempilharString(&pilha);
            char *operando1 = desempilharString(&pilha);

            char *novaExpressao = concatenarParaPreFixa(token, operando1, operando2);
            empilharString(&pilha, novaExpressao);

            free(operando1);
            if (operando2) free(operando2);
        }
        token = strtok(NULL, " ");
    }

    char* resultado = desempilharString(&pilha);
    return resultado;
}

int main() {
    char expressao[] = "2 3 + log 5 /";

    // Fazendo uma cópia da expressão para a conversão
    char* expressaoParaConversao = strdup(expressao);
    char* expressaoPreFixa = converterPosFixaParaPreFixa(expressaoParaConversao);
    printf("Expressão Pré-fixa: %s\n", expressaoPreFixa);
    free(expressaoPreFixa);
    free(expressaoParaConversao);

    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Resultado: %f\n", resultado);

    return 0;
}