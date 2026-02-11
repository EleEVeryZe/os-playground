#include <stdio.h>
#include <stdlib.h>

/*
Cópia de Vetor: Escreva uma função que recebe um vetor estático e retorna um ponteiro para uma cópia exata dele no heap.
*/
int *cpyArr(int *arr, int n) {
    int *newArr;
    if ((newArr = malloc(sizeof(int) * n)) == NULL) return NULL;
    int *strt = newArr;
    while (n--)
        *(newArr++) = *(arr++); 
    return strt;
}

int main() {
    int n = 5;
    int arr[] = {1, 2, 3, 4, 5};

    int *newArr = cpyArr(arr, n);
    int *strt = newArr;
    printf("New heap arr: \n");
    while (n--)
        printf("%d-%d\n", n, *(newArr++));
    free(strt);
}