#include <stdio.h>
/*
Cópia de String: Implemente sua própria versão de strcpy usando ponteiros.
*/

char* strcpy1(char *dest, char *src) {
    char *ret = dest;
    while (*(dest++) = *(src++))
    *dest = '\0';
    return ret;
}

int main() {
    char *src = "abbadabaduuu";
    
    char dest[20];

    if (dest == NULL) return 1;  

    strcpy1(dest, src);

    printf("%s", dest);
}