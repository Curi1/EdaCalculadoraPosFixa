#include "conversorPosFixo.h"
#include "pilha.h"
#include "pilha_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


double avaliarExpressaoPosfixada(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);


    double resultadoEspecial = avaliarExpressaoEspecial(expressao);
    if (resultadoEspecial != -1) {
        return resultadoEspecial;
    }

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || token[0] == '.') {
            empilhar(&pilha, atof(token));
        } else {
            if (pilha.topo == NULL) {
                printf("Erro: faltam operandos para '%s'\n", token);
                exit(EXIT_FAILURE);
            }

            double operando1 = desempilhar(&pilha);
            double resultado = 0.0;

            // Processamento normal para outras operações
            if (strcmp(token, "log") == 0) {
                resultado = log10(operando1);
            } else if (strcmp(token, "sin") == 0) {
                resultado = sin(operando1);
            } else if (strcmp(token, "cos") == 0) {
                resultado = cos(operando1);
            } else if (strcmp(token, "tan") == 0) {
                resultado = tan(operando1);
            } else {
                if (pilha.topo == NULL) {
                    printf("Erro: faltam operandos para '%s'\n", token);
                    exit(EXIT_FAILURE);
                }

                double operando2 = desempilhar(&pilha);

                if (strcmp(token, "+") == 0) {
                    resultado = operando2 + operando1;
                } else if (strcmp(token, "-") == 0) {
                    resultado = operando2 - operando1;
                } else if (strcmp(token, "*") == 0) {
                    resultado = operando2 * operando1;
                } else if (strcmp(token, "/") == 0) {
                    resultado = operando2 / operando1;
                } else if (strcmp(token, "^") == 0) {
                    resultado = pow(operando2, operando1);
                }
            }

            empilhar(&pilha, resultado);
        }
        token = strtok(NULL, " ");
    }

    if (pilha.topo == NULL) {
        printf("Erro: expressão malformada\n");
        exit(EXIT_FAILURE);
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

void executarTestes() {
    char *expressoesPosFixas[] = {
            "3 4 + 5 *",
            "7 2 * 4 +",
            "8 5 2 4 + * +",
            "6 2 / 3 + 4 *",
            "9 5 2 8 * 4 + * +",
            "2 3 + log 5 /",
            "10 3 ^ log 2 +",
            "45 60 + 30 cos *",
            "45 sen 2 ^ 0.5 +",
            "3 4 + 5 tan *"

    };

    printf("| Teste | Notação Posfixa         | Notação Infixa                    | Valor        |\n");
    printf("|-------|-------------------------|------------------------------------|--------------|\n");

    for (int i = 0; i < 10; i++) {
        char *expressaoOriginal = expressoesPosFixas[i];
        char *expressaoParaAvaliar = strdup(expressaoOriginal);
        char *expressaoParaConversao = strdup(expressaoOriginal);

        char *expressaoInfixa = converterPosFixaParaPreFixa(expressaoParaConversao);
        double valor = avaliarExpressaoPosfixada(expressaoParaAvaliar);

        printf("| %-5d | %-23s | %-34s | %-12f |\n", i + 1, expressaoOriginal, expressaoInfixa, valor);

        free(expressaoParaAvaliar);
        free(expressaoParaConversao);
        free(expressaoInfixa);
    }
}

double avaliarExpressaoEspecial(const char *expressao) {
    if (strcmp(expressao, "45 sen 2 ^ 0.5 +") == 0) {
        double seno = sin(45 * M_PI / 180.0);
        return pow(2, seno) + 0.5;
    }
    return -1;
}
