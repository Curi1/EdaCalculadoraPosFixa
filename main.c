#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "conversorPosFixo.h"


// inconsistencias de dadodos errado(10 log 3 ^ 2 +); certo(10 3 ^ log 2 +)
// inconsistencias de dadodos errado(0.5 45 sen 2 ^ +); certo("45 sen 2 ^ 0.5 +)

//| Teste | Notação Posfixa       | Notação Infixa                | Valor            |
//|-------|-----------------------|-------------------------------|------------------|
//| 1     | 3 4 + 5 *             | (3 + 4) * 5                   | 35               |
//| 2     | 7 2 * 4 +             | 7 * 2 + 4                     | 18               |
//| 3     | 8 5 2 4 + * +         | 8 + (5 * (2 + 4))             | 38               |
//| 4     | 6 2 / 3 + 4 *         | (6 / 2 + 3) * 4               | 24               |
//| 5     | 9 5 2 8 * 4 + * +     | 9 + (5 * (2 + 8 * 4))         | 109              |
//| 6     | 2 3 + log 5 /         | log(2 + 3) / 5                | Aprox. 0.140     |
//| 7     | 10 log 3 ^ 2 +        | 3^log10 + 2                   | 5                |
//| 8     | 45 60 + 30 cos *      | (45 + 60) * cos(30)           | Aprox. 16,20     |
//| 9     | 0.5 45 sen 2 ^ +      | 2 ^ sen(45) + 0,5             | Aprox. 2,30      |
//| 10    | 3 4 + 5 tan *         | (3 + 4) * tan(5)              | Aprox. -23,66    |


int main() {
    setlocale(LC_ALL, "Portuguese");
    executarTestes();
    return 0;
}


// CASO QUEIRA FAZER OS TESTES UM POR UM USE A MAIN DE BAIXO

//int main() {
//    char expressao[] = "10 3 ^ log 2 +";
//
//    // Fazendo uma cópia da expressão para a conversão
//    char* expressaoParaConversao = strdup(expressao);
//    char* expressaoPreFixa = converterPosFixaParaPreFixa(expressaoParaConversao);
//    printf("Expressão Pré-fixa: %s\n", expressaoPreFixa);
//    free(expressaoPreFixa);
//    free(expressaoParaConversao);
//
//    double resultado = avaliarExpressaoPosfixada(expressao);
//    printf("Resultado: %f\n", resultado);
//
//    return 0;
//}