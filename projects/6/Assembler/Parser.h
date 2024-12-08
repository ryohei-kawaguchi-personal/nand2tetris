#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>

extern FILE *inputFile, *outputFile;

void Parser(const char* inputFilePath);
bool hasMoreCommands();
void advance();
char* commandType();
char* symbol();
char* parserDest();
char* parserComp();
char* parserJump();

#endif