#include "Code.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *codeDest(char *mnemonic)
{
    static char dest[4];
    if (strcmp(mnemonic, "null") == 0)
    {
        strcpy(dest, "000");
    }
    else if (strcmp(mnemonic, "M") == 0)
    {
        strcpy(dest, "001");
    }
    else if (strcmp(mnemonic, "D") == 0)
    {
        strcpy(dest, "010");
    }
    else if (strcmp(mnemonic, "MD") == 0)
    {
        strcpy(dest, "011");
    }
    else if (strcmp(mnemonic, "A") == 0)
    {
        strcpy(dest, "100");
    }
    else if (strcmp(mnemonic, "AM") == 0)
    {
        strcpy(dest, "101");
    }
    else if (strcmp(mnemonic, "AD") == 0)
    {
        strcpy(dest, "110");
    }
    else if (strcmp(mnemonic, "AMD") == 0)
    {
        strcpy(dest, "111");
    }
    else
    {
        printf("unknown dest was entered.");
        exit(EXIT_FAILURE);
    }
    // printf("destBinary:%s\n", dest);
    return dest;
}

char *codeComp(char *mnemonic)
{
    static char comp[8];
    if (strcmp(mnemonic, "0") == 0)
    {
        strcpy(comp, "0101010");
    }
    else if (strcmp(mnemonic, "1") == 0)
    {
        strcpy(comp, "0111111");
    }
    else if (strcmp(mnemonic, "-1") == 0)
    {
        strcpy(comp, "0111010");
    }
    else if (strcmp(mnemonic, "D") == 0)
    {
        strcpy(comp, "0001100");
    }
    else if (strcmp(mnemonic, "A") == 0)
    {
        strcpy(comp, "0110000");
    }
    else if (strcmp(mnemonic, "M") == 0)
    {
        strcpy(comp, "1110000");
    }
    else if (strcmp(mnemonic, "!D") == 0)
    {
        strcpy(comp, "0001101");
    }
    else if (strcmp(mnemonic, "!A") == 0)
    {
        strcpy(comp, "0110001");
    }
    else if (strcmp(mnemonic, "!M") == 0)
    {
        strcpy(comp, "1110001");
    }
    else if (strcmp(mnemonic, "-D") == 0)
    {
        strcpy(comp, "0001111");
    }
    else if (strcmp(mnemonic, "-A") == 0)
    {
        strcpy(comp, "0110011");
    }
    else if (strcmp(mnemonic, "-M") == 0)
    {
        strcpy(comp, "1110011");
    }
    else if (strcmp(mnemonic, "D+1") == 0)
    {
        strcpy(comp, "0011111");
    }
    else if (strcmp(mnemonic, "A+1") == 0)
    {
        strcpy(comp, "0110111");
    }
    else if (strcmp(mnemonic, "M+1") == 0)
    {
        strcpy(comp, "1110111");
    }
    else if (strcmp(mnemonic, "D-1") == 0)
    {
        strcpy(comp, "0001110");
    }
    else if (strcmp(mnemonic, "A-1") == 0)
    {
        strcpy(comp, "0110010");
    }
    else if (strcmp(mnemonic, "M-1") == 0)
    {
        strcpy(comp, "1110010");
    }
    else if (strcmp(mnemonic, "D+A") == 0)
    {
        strcpy(comp, "0000010");
    }
    else if (strcmp(mnemonic, "D+M") == 0)
    {
        strcpy(comp, "1000010");
    }
    else if (strcmp(mnemonic, "D-A") == 0)
    {
        strcpy(comp, "0010011");
    }
    else if (strcmp(mnemonic, "D-M") == 0)
    {
        strcpy(comp, "1010011");
    }
    else if (strcmp(mnemonic, "A-D") == 0)
    {
        strcpy(comp, "0000111");
    }
    else if (strcmp(mnemonic, "M-D") == 0)
    {
        strcpy(comp, "1000111");
    }
    else if (strcmp(mnemonic, "D&A") == 0)
    {
        strcpy(comp, "0000000");
    }
    else if (strcmp(mnemonic, "D&M") == 0)
    {
        strcpy(comp, "1000000");
    }
    else if (strcmp(mnemonic, "D|A") == 0)
    {
        strcpy(comp, "0010101");
    }
    else if (strcmp(mnemonic, "D|M") == 0)
    {
        strcpy(comp, "1010101");
    }
    else
    {
        printf("unknown comp was entered.");
        exit(EXIT_FAILURE);
    }
    // printf("compBinary:%s\n", comp);
    return comp;
}

char *codeJump(char *mnemonic)
{
    static char jump[4];
    
    if (strcmp(mnemonic, "null") == 0)
    {
        strcpy(jump, "000");
    }
    else if (strcmp(mnemonic, "JGT") == 0)
    {
        strcpy(jump, "001");
    }
    else if (strcmp(mnemonic, "JEQ") == 0)
    {
        strcpy(jump, "010");
    }
    else if (strcmp(mnemonic, "JGE") == 0)
    {
        strcpy(jump, "011");
    }
    else if (strcmp(mnemonic, "JLT") == 0)
    {
        strcpy(jump, "100");
    }
    else if (strcmp(mnemonic, "JNE") == 0)
    {
        strcpy(jump, "101");
    }
    else if (strcmp(mnemonic, "JLE") == 0)
    {
        strcpy(jump, "110");
    }
    else if (strcmp(mnemonic, "JMP") == 0)
    {
        strcpy(jump, "111");
    }
    else
    {
        printf("unknown jump was entered.");
        exit(EXIT_FAILURE);
    }
    // printf("jumpBinary:%s\n", jump);
    return jump;
}