#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

void grava(FILE *exit, int *PC, int bitsMEM, int bitsCODE, char *code);

int achaLabel(Dados *celula, char *label);

void traduz(FILE *exit, char *linha, Lista enderecos, int *PC);

#endif
