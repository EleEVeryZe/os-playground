#include <stdio.h>
/*
Encontrar Maior: Crie uma função que receba um array e seu tamanho, e retorne um ponteiro para o maior elemento.
*/

int* greatest(int arr[5], int n) {
    int *greatest = &arr[0];

    for(int i = 1; i < n; i++){
        if (*greatest < *(arr + i))
            greatest = arr + i;
    }

    return greatest;
}

int main() {
    int arr[5] = {1,2,3,4,5};
    int *great = greatest(arr, 5);
    printf("Greatest is: %d\nPosition: %p", *great, great);
}