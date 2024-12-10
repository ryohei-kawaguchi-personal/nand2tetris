#ifndef SYMBOLE_TABLE_H
#define SYMBOLE_TABLE_H

#include <stdbool.h>

void SymbolTable();
void addEntry(char* symbol, int address);
bool contains(char* symbol);
int getAddress(char* symbol);

#endif

