#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define SYMBOL_SIZE 1000
#define MNEMONIC_SIZE 10

FILE *inputFile, *outputFile;
char CURRENT_COMMAND[256];

void Parser(const char* inputFilePath){
    // printf("inputFilePath=%s\n", inputFilePath);
    // 入力ファイルを開く
    inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    char outputFilePath[256];
    strcpy(outputFilePath, inputFilePath);
    
    // 文字列の最後の「.」のアドレスを返す
    char *dot = strrchr(outputFilePath, '.');
    
    // 拡張子が存在すればそれを置き換え、無ければ末尾に追加
    if (dot) {
        strcpy(dot, ".hack");
    } else {
        strcat(outputFilePath, "hack");
    }

    // printf("outputFilePath=%s\n", outputFilePath);

    // 出力ファイルを開く（存在しない場合は作成）
    outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        fclose(outputFile);
        exit(EXIT_FAILURE);
    }
}

// 入力にまだコマンドが存在するか
bool hasMoreCommands()
{
    long currentPosition = ftell(inputFile); // 現在の位置を記録
    if (fgets(CURRENT_COMMAND, sizeof(CURRENT_COMMAND), inputFile) == NULL)
    {
        return false;
    }
    fseek(inputFile, currentPosition, SEEK_SET); // ファイル位置を元に戻す
    return true;
}

// 入力から次のコマンドを読み、それを現在のコマンドにする
// hasMoreCommandsがtrueの場合のみ呼ぶ
void advance()
{
    fgets(CURRENT_COMMAND, sizeof(CURRENT_COMMAND), inputFile);
    CURRENT_COMMAND[strcspn(CURRENT_COMMAND, "\n")] = '\0';

    int i = 0, j = 0;
    // 空白文字をカットした文字列を格納する
    while (CURRENT_COMMAND[i] != '\0')
    {
        if (!isspace((unsigned char)CURRENT_COMMAND[i]))
        {
            CURRENT_COMMAND[j++] = CURRENT_COMMAND[i];
        }
        i++;
    }
    CURRENT_COMMAND[j] = '\0';

    // コメントアウトを削除
    i = 0;
    while (CURRENT_COMMAND[i] != '\0')
    {
        if (CURRENT_COMMAND[i] == '/' && CURRENT_COMMAND[i + 1] == '/')
        {
            break;
        }
        i++;
    }
    CURRENT_COMMAND[i] = '\0';

    // printf("%s\n", CURRENT_COMMAND);
}

// 現コマンドの種類を返す
// A_COMMAND:A命令
// C_COMMAND:C命令
// L_COMMAND:疑似コマンド
// N_COMMAND:空白行
char *commandType()
{
    if (CURRENT_COMMAND[0] == '\0')
    {
        return "N_COMMAND";
    }
    else if (CURRENT_COMMAND[0] == '@')
    {
        return "A_COMMAND";
    }
    else if (strchr(CURRENT_COMMAND, '=') != NULL || strchr(CURRENT_COMMAND, ';') != NULL)
    {
        return "C_COMMAND";
    }
    else if (CURRENT_COMMAND[0] == '(' && strchr(CURRENT_COMMAND, ')') != NULL)
    {
        return "L_COMMAND";
    }

    printf("unknown command was entered.");
    fclose(inputFile);
    fclose(outputFile);
    exit(EXIT_FAILURE);
}

// 現コマンドの@Xxxもしくは(Xxx)のXxxを返す
// commandTypeがA_COMMANDもしくはL_COMMANDのときのみ呼ばれる
char *symbol()
{
    char symbol[SYMBOL_SIZE];
    char *symbolPointer = symbol + 1;
    strcpy(symbol, CURRENT_COMMAND);

    char *end = NULL;

    end = strchr(symbolPointer, ')');
    if (end != NULL)
    {
        *end = '\0'; // 見つかった位置で文字列を切る
    }

    // printf("symbol:%s\n", symbolPointer);
    return symbolPointer;
}

// C命令のdestニーモニックを返す
char *parserDest()
{
    static char mnemonic[MNEMONIC_SIZE];
    strcpy(mnemonic, CURRENT_COMMAND);

    char *end = NULL;

    end = strchr(mnemonic, '=');
    if (end == NULL)
    {
        return "null";
    }
    else
    {
        *end = '\0'; // 見つかった位置で文字列を切る
    }
    // printf("dest:%s\n", mnemonic);
    return mnemonic;
}

// C命令のcompニーモニックを返す
char *parserComp()
{
    static char mnemonic[MNEMONIC_SIZE];
    strcpy(mnemonic, CURRENT_COMMAND);

    char *start = NULL;
    char *end = NULL;

    start = strchr(mnemonic, '=');
    end = strchr(mnemonic, ';');

    if (end != NULL)
    {
        *end = '\0';
    }

    if (start != NULL)
    {
        // printf("comp:%s\n", start + 1);
        return start + 1;
    }
    // printf("comp:%s\n", mnemonic);
    return mnemonic;
}

// C命令のjumpニーモニックを返す
char *parserJump()
{
    static char mnemonic[MNEMONIC_SIZE];
    strcpy(mnemonic, CURRENT_COMMAND);
    char *start = NULL;

    start = strchr(mnemonic, ';');
    if (start == NULL)
    {
        return "null";
    }
    // printf("jump:%s\n", start + 1);
    return start + 1;
}
