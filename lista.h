#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct Dados{
    char label[20];
    int PC; //linha em que se encontra o label
    struct Dados *prox;
}Dados;

typedef struct Lista{
    Dados *primeiro;
    Dados *ultimo;
}Lista;

void criaLista(Lista *lista);

void addDados(Lista *lista, Dados *celula, char *label, int PC);

void desalocaLista(Lista *lista);

#endif