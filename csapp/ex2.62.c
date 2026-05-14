/*
Write a function int_shifts_are_arithmetic() that yields 1 when run on a
machine that uses arithmetic right shifts for data type int and yields 0 otherwise.
Your code should work on a machine with any word size. Test your code on several
machines
*/

int int_shifts_are_arithmetic(){
    print_bits((unsigned char)(-1 >> 1)); 
    return (-1 >> 1) == -1;
}

void print_bits(unsigned char val) {
    printf("\nBits: ");
    for (int i = 7; i >= 0; i--) {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
    printf("\n");
}

int main() {
   printf("%d\n", int_shifts_are_arithmetic()); 
}