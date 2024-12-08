#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Code.h"

void decimalToBinary16(char* binaryStr, const char* decimalStr) {
    char* endptr;
    long decimal = strtol(decimalStr, &endptr, 10);

    if (*endptr != '\0' || decimal < 0 || decimal > 65535) {
        printf("unexpected decimal was entered.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 16; i++) {
        binaryStr[15 - i] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binaryStr[16] = '\0';
}

int main(int argc, char *argv[])
{
    char *type;
    char *aValue;
    char *destMnemonic;
    char *compMnemonic;
    char *jumpMnemonic;
    static char binary[16];
    // printf("before binary=%x\n", binary);

    // 引数の確認
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file> \n", argv[0]);
        return EXIT_FAILURE;
    }

    Parser(argv[1]);

    while (hasMoreCommands())
    {
        // printf("binary=%p\n", binary);
        advance();
        // printf("%s", CURRENT_COMMAND);
        type = commandType();
        // printf("%s\n", type);
        if (strcmp(type, "A_COMMAND") == 0 || strcmp(type, "L_COMMAND") == 0)
        {
            aValue = symbol();
            decimalToBinary16(binary, aValue);
            // printf("address=%p binary=%s\n", &binary, binary);
        }
        else if (strcmp(type, "C_COMMAND") == 0)
        {
            destMnemonic = parserDest();
            char *destBinary = codeDest(destMnemonic);
            compMnemonic = parserComp();
            char *compBinary = codeComp(compMnemonic);
            jumpMnemonic = parserJump();
            char *jumpBinary = codeJump(jumpMnemonic);

            strcpy(binary, "111");
            // printf("address=%p binary=%s\n", &binary, binary);
            strcat(binary, compBinary);
            strcat(binary, destBinary);
            strcat(binary, jumpBinary);
            // printf("address=%p binary=%s\n", &binary, binary);
            // printf("binary=%s\n", binary);
        }
        else
        {
            continue;
        }
        // printf("address=%p binary=%s\n", &binary, binary);
        fprintf(outputFile, "%s\n", binary);
    }

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}