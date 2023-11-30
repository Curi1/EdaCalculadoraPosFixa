#ifndef CONVERSOR_POS_FIXO_H
#define CONVERSOR_POS_FIXO_H

double avaliarExpressaoPosfixada(char *expressao);
int ehUnario(char* operador);
char* concatenarParaPreFixa(char* operador, char* operando1, char* operando2);
char* converterPosFixaParaPreFixa(char *expressao);

#endif