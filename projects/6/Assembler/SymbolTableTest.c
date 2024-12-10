#include <stdio.h>
#include "SymbolTable.h"

int main(void){
    SymbolTable();
    addEntry("test",1);
    addEntry("test20",20);

    printf("address=%d\n", getAddress("R13"));
    printf("address=%d\n", getAddress("KBD"));
    printf("address=%d\n", getAddress("test20"));
    return 0;
}