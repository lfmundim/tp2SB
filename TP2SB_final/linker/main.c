#include "tp1.h"
void updateLabels(FILE* input, FILE* output, Lista labels){
    
    char c;
    char *label, *Label;
    char *out;
    while (fscanf(input, "%c", &c) != EOF) {
        if(c == '_'){
            label = (char*) calloc(50, sizeof(char));
            Label = (char*) calloc(50, sizeof(char));
            Label[0] = '_';
            out = (char*) calloc(8, sizeof(char));
            fscanf(input, "%[^\n]\n", label);
            strcat(Label, label);
            out = convertNumber(achaLabel(labels.primeiro->prox, Label), 8);
            fprintf(output, "%s;\n", out);
            free(out);
            free(label);
            free(Label);
        }
        else{
            fprintf(output, "%c", c);
        }
    }
}


int main(int argc, char* argv[]){
    int num, largura, size = 0;
    int i = 1, j, k;
    char *text, *label, *posicao, *numBin, *code;
    Lista enderecos;
    FILE *temp, *file, *exit;
    
    temp = fopen("temp.txt", "wt");
    text = (char*)calloc(100,sizeof(char));
    numBin = (char*)calloc(8, sizeof(char));
    criaLista(&enderecos);
    
    while(i<argc){ // mudar
        file = fopen(argv[i], "rt");
        fscanf(file, "%[^\n]\n", text); // lê a primeira linha do arquivo
        largura = atoi(text);
        for (j=0; j<largura; j++) { // lê as linhas de codigo
            code = (char*)calloc(50, sizeof(char));
            fscanf(file, "%d : ", &num);
            numBin = convertNumber(num+size, 8);
            fprintf(temp, "%s : ", numBin);
            fscanf(file, "%[^\n]\n", code);
            fprintf(temp, "%s\n", code);
            free(code);
        }
        while(fscanf(file, "%[^\n]\n", text) != EOF){ // lê as labels
            label = (char*)calloc(100, sizeof(char));
            posicao = (char*)calloc(10, sizeof(char));
            for(j = 0; text[j] != ' '; j++){
                label[j] = text[j];
            }
            for(j = j+1, k = 0; text[j] != '\0'; j++, k++){
                posicao[k] = text[j];
            }
            addDados(&enderecos, enderecos.ultimo, label, atoi(posicao)+size); // adicionar label na lista
            free(label);
            free(posicao);
        }
        size += largura;
        i++;
        fclose(file);
    }
    fclose(temp);
    temp = fopen("temp.txt", "rt");
    exit = fopen("saida.mif", "wt");
    
    fprintf(exit, "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = BIN;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n\n");
    updateLabels(temp, exit, enderecos);//PASSO 2: SUBSTITUIR AS LABELS
    fprintf(exit, "[%s..11111111] : 00000000;\nEND;\n", convertNumber(size, 8));
    
    desalocaLista(&enderecos);
    free(numBin);
    
    return 0;
}
