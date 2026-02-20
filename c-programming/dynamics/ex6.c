#include <stdlib.h>
#include <stdio.h>
/*

Matriz Dinâmica (Linha Única): Aloque uma matriz $M \times N$ como um único bloco de memória e acesse os elementos via ptr[i * N + j].
*/

int matrix(int m, int n) {

    int **matrix = (int **) malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++)
    {
       
        *(matrix + i) = (int *) malloc((n+1) * sizeof(int));
       for (int j = 0; j < n; j++)
       {
            printf("Provide the element [%d, %d]: ", i, j);
            scanf("%d", (*(matrix + i) + j));
            printf("\n");
       }
    }
    
    for (int i = 0; i < m; i++)
    {
       for (int j = 0; j < n; j++)
       {
            printf("%d\n", *(*(matrix + i) + j));
       }
    }
 
}

int main() {
    matrix(2, 3);
}