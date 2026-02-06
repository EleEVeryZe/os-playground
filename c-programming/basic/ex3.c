#include <stdio.h>
/**
 * Aritmética Simples: Crie um array de 5 inteiros. Use um ponteiro para percorrer o array e imprimir os valores sem usar colchetes [].
 */

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    int i = 0;

    while (i < 60) {
        printf("i: %d | v: %p\n", i , (arr + i));
        i++;
    }

    return 0;
}