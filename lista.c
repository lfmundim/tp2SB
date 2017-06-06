#include "tp1.h"

void criaLista(Lista *lista){
    lista->primeiro = (Dados*) calloc(1, sizeof(Dados));
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

void addDados(Lista *lista, Dados *celula, char *label, int PC){
    int i;
    Dados *novo;
    novo = (Dados*) calloc(1, sizeof(Dados));
    for(i=0; label[i] != '\0'; i++){
        novo->label[i] = label[i];
    }
    novo->label[i] = '\0';
    novo->PC = PC;
    novo->prox = celula->prox;
    celula->prox = novo;
    lista->ultimo = novo;
}

void desalocaLista(Lista *lista){
    Dados *aux;
    while(lista->primeiro != NULL){
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        free(aux);
    }
}
