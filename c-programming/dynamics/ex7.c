#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/*
Filtro de Pares: Receba um array e retorne um novo array (alocado dinamicamente) contendo apenas os números pares do original.
*/

int* getEvens(int *arr, int n) {
    int numEven = 0;
    for (int i = 0; i < n; i++)
        if (*(arr + i) % 2 == 0)
            numEven++;
   
    int *allEven;
    if ((allEven = malloc(numEven * sizeof(int) + sizeof(int))) == NULL)
        return NULL;

    int current = 1;
     for (int i = 0; i < n; i++)
        if (*(arr + i) % 2 == 0)
            *(allEven + current++) = *(arr + i);
    
    *(allEven) = numEven; 
    return allEven;
}

int main() {
    int arr[7] = {1, 2, 3, 4, 5, 6, 7};
    printf("Should print only the even numbers\n");
    int *evenNums = getEvens(arr, 7);
    
    for (int i = 1; i <= *(evenNums); i++)
        printf("%d %d\n", i, *(evenNums + i));

    free(evenNums);
}