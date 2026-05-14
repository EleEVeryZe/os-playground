/*
Write C expressions that evaluate to 1 when the following conditions are true and
to 0 when they are false. Assume x is of type int.
A. Any bit of x equals 1.
B. Any bit of x equals 0.
*/

int anyBitIsOne(int x){
    return !!x;    
}

int main() {
    printf("%d\n", anyBitIsOne(1));
    printf("%d\n", anyBitIsOne(0));
    printf("%d\n", anyBitIsOne(1));
}