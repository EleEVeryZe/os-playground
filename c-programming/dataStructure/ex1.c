#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
    Matriz Dinâmica de Ponteiros: Aloque uma matriz usando um array de ponteiros (ponteiro para ponteiro).
*/
int main() {
    printf("Start of function");
    int cols = 30;
    int rows = 30;
    int **ptrToPrt;
    if ((ptrToPrt = malloc(sizeof(int *) * rows)) == NULL) return NULL; 

    for (int i = 0; i < rows; i++)
        if (((*(ptrToPrt + i)) = malloc(sizeof(int) * cols)) == NULL) break;
    
    for (int i = 0; i < rows; i++)
        free( (*(ptrToPrt + i)) ); 

    free(ptrToPrt);
    printf("End of function");
}