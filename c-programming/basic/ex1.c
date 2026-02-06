#include <stdio.h>
//1. Troca de Valores: Crie uma função swap(int *a, int *b) que troca os valores de duas variáveis.

void swap(int *a, int *b) {
    int holder = *a;
    *a = *b;
    *b = holder;
}

int main() {
    int a = 10;
    int b = 20;
    printf("Swap these two position: %d %d \n", a, b);
    swap(&a, &b);
    printf("%d %d", a, b);
}
