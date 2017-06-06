#include "tp1.h"

char* convertNumber(int number, int bits){
    char* binary;
    int i, k;

    binary = (char*)calloc(bits, sizeof(char));

    for(i=bits-1; i>=0; i--){
        k = number >> i;
        if(k&1)
            binary[bits-i-1]='1';
        else
            binary[bits-i-1]='0';
    }
    return binary;
}
