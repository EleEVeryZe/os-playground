#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
Redimensionamento com Realloc: Aloque um array de 5 posições, preencha-o e depois use realloc para aumentar para 10.
*/

int main() {
    char *arr = malloc(sizeof(char) * 8);
    strcpy(arr, "Rodolfo");

    printf("%s", arr);
    
    char *temp;
    if ((temp = realloc(arr, 20)) == NULL) return NULL;

    arr = temp;
    free(temp);  
    
    strcpy(arr, "Rodolfo Elizer");

    printf("%s", arr);

    free(arr);
}