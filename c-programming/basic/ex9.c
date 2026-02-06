#include <stdio.h>
/*
Comparação de Strings: Implemente sua versão de strcmp usando ponteiros.
*/

int strcmp1(char *a, char *b) {
    while (*(a) != '\0' || *(b) != '\0') if (*(a++) != *(b++)) return 0;
    return 1;
}

int main() {
    char *a = "abba";
    char *b = "abba";
    printf("A == B? %d", strcmp1(a, b));
}