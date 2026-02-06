#include <stdio.h>
/*
Soma com Ponteiros: Escreva uma função que receba dois números via ponteiros e retorne a soma deles.
*/

int soma(int *a, int *b) {
    return *a + *b;
}

int main() {
    int a = 10;
    int b = 20;
    printf("%d + %d=%d", a, b, soma(&a, &b));
}