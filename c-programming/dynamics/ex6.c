#include <stdlib.h>
#include <stdio.h>
/*

Matriz Dinâmica (Linha Única): Aloque uma matriz $M \times N$ como um único bloco de memória e acesse os elementos via ptr[i * N + j].
*/

int *matrix(int n, int m) {     
    
    int n2 = n;
    int m2 = m;
    int (*matrix)[n] = malloc(sizeof(int) * n * m);
    int *start[n] = &matrix;
    while (n) {
        while (m) {
            scanf("%d", &matrix[m--][n--]);
        }
    }

    while (n2--)
        while (m2--)
            printf("%d", start[m2--][n2--]);
}

int main() {
    matrix(2, 3);
}