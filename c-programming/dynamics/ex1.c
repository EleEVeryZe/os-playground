#include <stdio.h>
#include <stdlib.h>
/*
Vetor Dinâmico: Peça ao usuário um tamanho $n$, aloque um array de inteiros com malloc, preencha-o e libere a memória.
*/
int main() {
    int n;
    
    printf("Give me an n, please.\n");
    scanf("%d", &n);

    int *arr = malloc(sizeof(int) * n);
    int *pos1 = arr;

    printf("Creating an array of size %d\n", n);

    while (n) {
        printf("I: %d", n);
        *(arr++) = n--;
    }

    free(pos1);

    return 0;
}