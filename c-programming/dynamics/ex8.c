#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
Leitura de String Indeterminada: Leia caracteres do teclado um por um e use realloc para expandir o buffer até que o usuário aperte "Enter".
*/
int main() {
    char *d;
    if ((d = malloc(1)) == NULL) return NULL;
    int i = 1;
    bool isRunning = true; 
    char c;
    printf("Type something and press ENTER");
    while (isRunning){
       if (scanf("%c", &c) != 1) break;

       if (c == '\n'){
            c = '\0';
           isRunning = false;
       }
       
       if ((d = realloc(d, sizeof(char) * i)) == NULL) break; 
       d[i - 1] = c;
       i++;
    }
    printf("Value: %s\n", d);
    free(d);
}