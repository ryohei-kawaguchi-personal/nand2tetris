#include "SymbolTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SYMBOL_SIZE 1000
#define ADDRESS_SIZE 24576
#define MAP_ENTRY_SIZE 10000

typedef struct entries
{
    char symbol[SYMBOL_SIZE];
    char address[ADDRESS_SIZE];
} MapEntry;

typedef struct symbolMap
{
    MapEntry entries[MAP_ENTRY_SIZE];
    int size;
} SymbolMap;

SymbolMap symbolMap;
SymbolMap *symbolMapP = &symbolMap;

void SymbolTable()
{
    symbolMapP->size = 0;
    int i;
    for (i = 0; i <= 15; i++)
    {
        char registerSymbol[5] = "R";
        char registerSymbolNum[5];
        sprintf(registerSymbolNum, "%d", i);
        strcat(registerSymbol, registerSymbolNum);
        addEntry(registerSymbol, i);
    }

    addEntry("SP", 0);
    addEntry("LCL", 1);
    addEntry("ARG", 2);
    addEntry("THIS", 3);
    addEntry("THAT", 4);
    addEntry("SCREEN", 16384);
    addEntry("KBD", 24576);
}

// テーブルに(symbol.adress)のペアを追加する
void addEntry(char *symbol, int address)
{
    for (int i = 0; i < symbolMapP->size; i++)
    {
        if (strcmp(symbolMapP->entries[i].symbol, symbol) == 0)
        {
            return;
        }
    }

    if (symbolMapP->size < SYMBOL_SIZE)
    {
        strcpy(symbolMapP->entries[symbolMapP->size].symbol, symbol);
        sprintf(symbolMapP->entries[symbolMapP->size].address, "%d", address);
        symbolMapP->size++;
    }
    // printf("push {symbol=%s, address=%s}\n", symbolMapP->entries[symbolMapP->size - 1].symbol, symbolMapP->entries[symbolMapP->size - 1].address);
}

// シンボルテーブルは与えられたsymbolを含むか
bool contains(char *symbol)
{
    for (int i = 0; i < symbolMapP->size; i++)
    {
        if (strcmp(symbolMapP->entries[i].symbol, symbol) == 0)
        {
            return true;
        }
    }
    return false;
}

// symbolに結びつけられたアドレスを返す
int getAddress(char *symbol)
{
    for (int i = 0; i < symbolMapP->size; i++)
    {
        if (strcmp(symbolMapP->entries[i].symbol, symbol) == 0)
        {
            return atoi(symbolMapP->entries[i].address);
        }
    }
    return -1;
}