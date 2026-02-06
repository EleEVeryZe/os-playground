#include <stdio.h>
#include <stdlib.h>
/*
Inversão de String: Use dois ponteiros (um no início e outro no fim) para inverter uma string "in-place".
*/

char* inverter(char *strg, char *inverted, int n) {
    int j = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        inverted[i] = *(strg + j++);
    }

    inverted[n] = '\0';

    return inverted;
}

char* inPlaceInverter(char *strg, int n) {
    char *inicio = strg;
    char *fim = strg + (n - 1);

    while (inicio < fim) {
        char aux = *inicio;
        *inicio = *fim;
        *fim = aux;

        inicio++;
        fim--;
    }
    return strg;
}

int* somaNBit(int *a, int *b, int n) {
    int *c = malloc((n + 1) * sizeof(int));
    if (c == NULL) return NULL;

    int r = 0;
    int i = n - 1;
    for (; i >= 0; i--){        
        int sum = *(a + i) + *(b + i) + r;
        int mod = sum % 2;
        *(c + (i + 1)) = mod;
        r = sum / 2; 
        
        printf("%d + %d\n", *(a + i), *(b + i));
    }

    *(c + 0) = r;

    printf("C: ");
    while (++i < n + 1)
        printf("%d ", *(c + i));
    printf("\n");
    return c;
}

int main() {
    int a[] = {1, 0, 1, 1};
    int b[] = {1, 0, 1, 1};
    somaNBit(&a, &b, 4); // = {1, 0, 1, 1, 0};
}

int main2() {
    char inplace[] = "in-place";
    char invertido[sizeof(inplace)];
    inPlaceInverter(inplace, 8);
}