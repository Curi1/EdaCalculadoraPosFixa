#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversorPosFixo.h"


// inconsistencias de dadodos errado(10 log 3 ^ 2 +); certo(10 3 ^ log 2 +)

int main() {
    char expressao[] = "10 3 ^ log 2 +";

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