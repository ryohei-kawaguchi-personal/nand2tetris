#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char* binary = malloc(16);
    strcpy(binary, "000");
    char* destBinary = "111";
    char* compBinary = "222";
    char* jumpBinary = "333";

    printf("address=%p binary=%s\n", binary, binary);

    strcat(binary, destBinary);
    strcat(binary, compBinary);
    strcat(binary, jumpBinary);

    printf("address=%p binary=%s\n", binary, binary);

    free(binary);
    return 0;
}