#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Média Dinâmica: Aloque espaço para $n$ floats, calcule a média e exiba o resultado.
*/
int main() {
    srand((unsigned int)time(NULL));

    int n;
    printf("Give me an N\n");
    scanf("%d", &n);
    float *flt;
    if ((flt = malloc(sizeof(float) * n)) == NULL) return 1;

    float *strt = flt;

    int i = 0;
    while (i++ < n) {
        float random_float = (float)rand() / (float)RAND_MAX;
        printf("%f\n", random_float);
        *(flt++) = random_float;
    }

    flt = strt;

    float *sum;    
    if ((sum = malloc(sizeof(float))) == NULL) return 1;

    while (i--)
        *sum += *(flt++);
        
    printf("Avarage: %f\n", (*sum / (float)n));

    free(strt);

    return 0;
}