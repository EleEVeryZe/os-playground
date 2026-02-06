#include <stdio.h>
//Impressão de Endereço: Declare uma variável e um ponteiro para ela. Imprima o valor da variável, 
//o endereço dela e o valor armazenado no ponteiro.

int main() {
    int a = 10;
    int *p_a = &a;
    
    printf("a: %p, endereco de a: %p\n", (void *)&a, (void *)p_a);
    printf("a: %d, endereco de p_a: %p\n", a, (void *)&p_a);
    printf("a: %d, *valor dentro de p_a: %d\n", a, *p_a);
}