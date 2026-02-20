#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
Limpeza de Memória: Escreva um programa que aloque uma matriz de structs e garanta que não haja "memory leak" (use o Valgrind se possível).
*/
typedef struct {
    char *name;
} Person;

int main() {
    int rows = 2;
    int cols = 2;

    Person **people;
    if ((people = malloc(rows * sizeof(Person *))) == NULL) return NULL;    

    for (int i = 0; i < cols; i++)
        if ((people[i] = malloc(cols * sizeof(Person))) == NULL)
            break;

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < cols; j++) 
            {
                if ((people[i][j].name = malloc(sizeof(char) * 10)) == NULL) return NULL;
                strcpy(people[i][j].name, "Rodolfo");
            }
           
    printf("%s", ((*(*(people + 0) + 0)).name));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            free(people[i][j].name);
        }
        free(people[i]);
   }    
   free(people);
}
