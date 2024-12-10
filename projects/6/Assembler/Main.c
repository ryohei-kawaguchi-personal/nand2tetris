#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

int address = 16;

bool isNumeric(const char *str)
{
    char *endptr;
    if (*str == '\0')
        return false; // 空文字列は数値ではない

    // `strtol`で変換を試みる
    strtol(str, &endptr, 10);

    // 変換できた場合、`endptr`は文字列の終端を指すはず
    return *endptr == '\0';
}

void decimalToBinary16(char *binaryStr, const char *decimalStr)
{
    char *endptr;
    long decimal = strtol(decimalStr, &endptr, 10);

    if (*endptr != '\0' || decimal < 0 || decimal > 65535)
    {
        printf("unexpected decimal was entered.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 16; i++)
    {
        binaryStr[15 - i] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binaryStr[16] = '\0';
}

void symbolTobinary(char *binaryStr, char *symbolPointer){
    static char addressStr[10];
    if (contains(symbolPointer))
    {
        sprintf(addressStr, "%d", getAddress(symbolPointer));
        decimalToBinary16(binaryStr, addressStr);
    }
    else
    {
        addEntry(symbolPointer, address);
        sprintf(addressStr, "%d", address);
        decimalToBinary16(binaryStr, addressStr);
        address++;
    }
}

void firstPath()
{
    char *type;
    int row = 0;

    while (hasMoreCommands())
    {
        advance();
        type = commandType();
        if (strcmp(type, "A_COMMAND") == 0 || strcmp(type, "C_COMMAND") == 0)
        {
            row++;
        }
        else if (strcmp(type, "L_COMMAND") == 0)
        {
            addEntry(symbol(), row);
        }
        else
        {
            continue;
        }
    }
}

void secondPath()
{
    char *type;
    char *symbolPointer;
    char *destMnemonic;
    char *compMnemonic;
    char *jumpMnemonic;
    static char binary[16];

    while (hasMoreCommands())
    {
        advance();
        type = commandType();
        if (strcmp(type, "A_COMMAND") == 0)
        {
            symbolPointer = symbol();
            if (isNumeric(symbolPointer))
            {
                decimalToBinary16(binary, symbolPointer);
            }
            else
            {
                symbolTobinary(binary, symbolPointer);
            }
            // printf("binary=%s\n", binary);
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
            strcat(binary, compBinary);
            strcat(binary, destBinary);
            strcat(binary, jumpBinary);
        }
        else
        {
            continue;
        }
        // printf("address=%p binary=%s\n", &binary, binary);
        fprintf(outputFile, "%s\n", binary);
    }
}

int main(int argc, char *argv[])
{
    // 引数の確認
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file> \n", argv[0]);
        return EXIT_FAILURE;
    }

    Parser(argv[1]);
    SymbolTable();
    long inputFileFirstPosition = ftell(inputFile); // 最初の位置を記録
    firstPath();
    fseek(inputFile, inputFileFirstPosition, SEEK_SET); // ファイル位置を元に戻す
    secondPath();

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}