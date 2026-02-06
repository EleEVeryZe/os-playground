/*
Ponteiro para Ponteiro: Crie um int x, um ponteiro *p para x, e um ponteiro **pp para p. Modifique x através de pp.
*/
int main() {
    int x = 10;
    int *p = &x;
    int **pp = &p;

    *(*(pp))=20;

    printf("%d", x);
}