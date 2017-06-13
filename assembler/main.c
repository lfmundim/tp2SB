#include "tp1.h"

int main(int argc, char* argv[]){
    int PC = 0, i, j, bytes;
    unsigned long int size;
    char *token, *text, *label;
    (void)argc;
    Lista enderecos; //ha dois tipos de label que podem ser encontrados
    FILE *file;
    FILE *exit;
    
    token = (char*)calloc(100,sizeof(char));
    text = (char*)calloc(1000,sizeof(char));
    file = fopen(argv[1], "rt");
    exit = fopen(argv[2], "wt");
    criaLista(&enderecos);
    
    
    // PASSO 1
    while(fscanf(file, "%[^\n]\n", text) != EOF){
        token = strtok(text, ";");
        if(token[0]=='_'){ // caso haja uma label
            label = (char*)calloc(32,sizeof(char)); // Inicia uma nova label
            for(i = 0; token[i] != ':'; i++){
                label[i] = token[i];
            }
            while(token[++i] == ' '){ // anda pos label, olhando o tipo
            }
            if(token[i] == '.'){
                if(token[i+1] == 'd'){ // caso .data
                    while(token[++i] != ' '){ // termina de ler os caracteres do ".data"
                    }
                    while(token[++i] == ' '){ // le os espaços em branco até achar o numero de bytes especificado
                    }
                    bytes = atoi(&token[i]);
                    addDados(&enderecos, enderecos.ultimo, label, PC);
                    PC+=bytes;    // PC incrementado de acordo com os bytes alocados
                }
            }
            else { // caso não .data
                addDados(&enderecos, enderecos.ultimo, label, PC);
                PC += 2;
            }
            free(label); // Descarta label utilizada
        }
        else PC += 2; // caso nao haja uma label
    }
    
    fprintf(exit, "%d\n", PC); // grava o tamanho do arquivo
    
    free(token);
    rewind(file);
    token = (char*)calloc(100, sizeof(char));
    PC = 0;
    
    // PASSO 2
    while(fscanf(file, "%[^\n]\n", text) != EOF){
        i = 0;
        if(text[0] == '_'){
            while(text[i]!=':')
                i++;
            i++;
            while(text[i]==' ')
                i++;
            
            size = strlen(text);
            for(j=0; i<(int)size; j++, i++)
                token[j] = text[i];
            for(i=j; i<=(int)strlen(token); i++)
                token[i] = '\0';
        }
        
        else{
            size = strlen(text);
            for(j=0; j<(int)size; j++)
                token[j] = text[j];
            for(i=j; i<=(int)strlen(token); i++)
                token[i] = '\0';
        }
        
        traduz(exit, token, &PC);
    }
    imprimeListaArq(exit, enderecos);
    
    free(token);
    desalocaLista(&enderecos);
    fclose(exit);
    fclose(file);
    return 0;
}
