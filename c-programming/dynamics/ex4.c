#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
Estrutura Dinâmica: Defina uma struct Aluno (nome e nota). Aloque um aluno dinamicamente, atribua valores e limpe a memória.
*/

typedef struct {
    char *nome;
    int nota;
} Aluno;

int main() {
    Aluno *aluno;
    if (((aluno = malloc(sizeof(Aluno))) == NULL)) return 1;
    char *myName = "Rodolfo";

    if ((aluno->nome = malloc(sizeof(strlen(myName) + 1))) == NULL) return 1;


    aluno->nota = 10;
    strcpy(aluno->nome, myName);
    
    printf("Hi. My name is %s, and I scored %d in math test\n", aluno->nome, aluno->nota);
    
    free(aluno->nome);
    free(aluno);

    return 0;
}