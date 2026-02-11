#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
Concatenação de Strings: Receba duas strings e aloque dinamicamente uma terceira string que seja a junção das duas.
*/

char *concat(char *a, char *b) {
	int sizeOfAB = 0;
	char *strtA = a;
	char *strtB = b;

	while (*(a++) != '\0')
		sizeOfAB++;

	while (*(b++) != '\0')
		sizeOfAB++;

	char *c;
       	if ((c = malloc(sizeof(char) * sizeOfAB)) == NULL) return NULL;

	char *strtOfC = c;

	while (*(strtA) != '\0')
		*(c++) = *(strtA++);

	while (*(strtB) != '\0')
		*(c++) = *(strtB++);

	*(c++) = '\0';

	return strtOfC;

}

int main() {
	char *a = "this is strgA";
	char *b = "this is  the strgB";
	

	char *c = concat(a, b);
	printf("Concatenating a + b: '%s'\n", c);
	free(c);
			
}


