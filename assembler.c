#include "tp1.h"

void grava(FILE *exit, int *PC, int bitsMEM, int bitsCODE, char *code){
    int i=0;
    fprintf(exit, "%s : ", convertNumber(*PC, 8));
    while(i<bitsCODE){
        fprintf(exit, "%c", code[i]);
        i++;
        if(i%bitsMEM == 0){
            fprintf(exit, ";\n");
            PC[0]++;
            if(i != bitsCODE) {
                fprintf(exit, "%s : ", convertNumber(*PC, 8));
            }
        }
    }
}

int achaLabel(Dados *celula, char *label){
    int PC;
    if (strcmp(label, celula->label) == 0){
        PC = celula->PC;
    }
    else{
        PC = achaLabel(celula->prox, label);
    }
    return PC;
}

void traduz(FILE *exit, char *linha, Lista enderecos, int *PC){
    int i=0, j=0, reg1, reg2;
    char *code, *func, *address, *reg1Bin, *reg2Bin; //codigo em binario
    func = (char*)calloc(10,sizeof(char));
    address = (char*)calloc(100,sizeof(char));

    while (linha[i] == ' ') {
        i++;
    }
    while(linha[i]!=' '){
        func[j] = linha[i];
        i++;
        j++;
    }
    while(linha[i]==' ') i++;

    if(func[0] != '.'){  // caso nao um .data

        if(strcmp(func,"exit") == 0){
            code = (char*)calloc(16,sizeof(char));
            memset(code, '0', 16);
        }


        else if(strcmp(func,"loadi") == 0){ // [5]bin+[3]reg+[8]address
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address[0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else if (strcmp(address, "IO") == 0){
                reg2 = 254;
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));
            strcpy(code, "00001");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"storei") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address
               [0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else if (strcmp(address, "IO") == 0){
                reg2 = 254;
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));
            strcpy(code, "00010");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"add") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "00011");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");
        }


        else if(strcmp(func,"subtract") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "00100");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");

        }


        else if(strcmp(func,"multiply") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "00101");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");
        }


        else if(strcmp(func,"divide") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "00110");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");

        }


        else if(strcmp(func,"jump") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address[0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "00111000");
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"jmpz") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address[0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "01000");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"jmpn") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address[0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "01001");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"move") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "01010");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");

        }


        else if(strcmp(func,"load") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "01011");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");
        }


        else if(strcmp(func,"store") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "01100");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");

        }


        else if(strcmp(func,"loadc") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                j++;
                i++;
            }
            reg2 = atoi(address);
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "01101");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"clear") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }


            strcpy(code, "01110");
            strcat(code, reg1Bin);
            strcat(code, "00000000");
        }


        else if(strcmp(func,"negate") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(3,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }
            while(linha[i]!='R' && linha[i]!='A') i++;
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg2 = atoi(&linha[i]);
                strcpy(reg2Bin, convertNumber(reg2, 3));
            }

            strcpy(code, "01111");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
            strcat(code, "00000");
        }


        else if(strcmp(func,"push") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }


            strcpy(code, "10000");
            strcat(code, reg1Bin);
            strcat(code, "00000000");
        }


        else if(strcmp(func,"pop") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
            }


            strcpy(code, "10001");
            strcat(code, reg1Bin);
            strcat(code, "00000000");
        }


        else if(strcmp(func,"addi") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            if(linha[i]=='R' || linha[i]=='A'){
                i++;
                reg1 = atoi(&linha[i++]);
                strcpy(reg1Bin, convertNumber(reg1, 3));
                //converter reg1 para binario 3 bits
            }
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            reg2 = atoi(address);
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "10010");
            strcat(code, reg1Bin);
            strcat(code, reg2Bin);
        }


        else if(strcmp(func,"call") == 0){
            code = (char*)calloc(16,sizeof(char));
            reg1Bin = (char*)calloc(3,sizeof(char));
            reg2Bin = (char*)calloc(8,sizeof(char));
            while(linha[i]==' ') i++;
            j=0;
            while(linha[i] != ' ' && linha[i] != '\0' && linha[i] != ';'){
                address[j] = linha[i];
                i++;
                j++;
            }
            if(address[0] == '_'){
                reg2 = achaLabel(enderecos.primeiro->prox, address);
            }
            else {
                reg2 = atoi(address);
            }
            strcpy(reg2Bin, convertNumber(reg2, 8));

            strcpy(code, "10011000");
            strcat(code, reg2Bin);
        }


        else { // função return
            code = (char*)calloc(16,sizeof(char));
            strcpy(code, "1010000000000000");
        }

        grava(exit, PC, 8, 16, code);
    }

    else {  // caso .data
        reg1 = atoi(&linha[i]);
        code = (char*)calloc(8*reg1, sizeof(char));
        while(linha[i] != ' ') i++;
        while(linha[i] == ' ') i++;
        reg2 = atoi(&linha[i]);
        strcpy(code, convertNumber(reg2, 8*reg1));
        grava(exit, PC, 8, 8*reg1, code);
    }

    free(address);
    free(func);
    free(code);
}
