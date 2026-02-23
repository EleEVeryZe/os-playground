#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
	22. Multiplicação de Matrizes Dinâmicas: Implemente a multiplicação de duas matrizes alocadas dinamicamente.
*/
int main() {
    printf("Start\n");
    int col = 3;
    int row = 3;
    
    int **mat1;
    int **mat2;

    if ((mat1 = malloc(sizeof(int *) * row)) == NULL) return NULL;
    if ((mat2 = malloc(sizeof(int *) * row)) == NULL) return NULL;

    for (int i = 0; i < row; i++)
    {
        if ((*(mat1 + i) = malloc(sizeof(int) * col)) == NULL) break;
        if ((*(mat2 + i) = malloc(sizeof(int) * col)) == NULL) break;

        for (int j = 0; j < col; j++)
        {
            *(*(mat1 + i) + j) = i * j;
            *(*(mat2 + i) + j) = j + i;
        }
        
    }
    int sum = 0;
    int a;
    int b;    
    for (int i = 0; i < row; i++)
    {
       for (int j = 0; j < col; j++)
        {
            a = *(*(mat1 + i) + j);
            b = *(*(mat2 + i) + j);
            printf("Operations: %d + %d = %d\n", a, b, (a + b));
            sum += a + b;
            
        }
        
        free(*(mat1 + i));
        free(*(mat2 + i));
    }    
    free(mat1);
    free(mat2);
    printf("Total sum: %d\n", sum);
}