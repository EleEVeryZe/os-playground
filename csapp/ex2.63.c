/*
Fill in code for the following C functions.

Function srl performs a logical right
shift using an arithmetic right shift (given by value xsra),
followed by other operations not including right shifts or division.

Function sra performs an arithmetic
right shift using a logical right shift (given by value xsrl), followed by other
operations not including right shifts or division. You may use the computation
8*sizeof(int) to determine w, the number of bits in data type int.

The shift amount k can range from 0 to w − 1.

*/

void print_bits(unsigned val)
{
    printf("\nBits: ");
    int fourAndFour = 0;
    for (int i = 31; i >= 0; i--)
    {
        if (fourAndFour != 0 && fourAndFour % 4 == 0)
            printf(".");
        printf("%c", (val & (1 << i)) ? '1' : '0');
        fourAndFour++;
    }
    printf("\n");
}

/*Perform shift arithmetically */
unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int)x >> k;
    // continues
    return xsra;
}

/* Perform shift logically */
int sra(int x, int k)
{
    int xsrl = (unsigned)x >> k;
    unsigned mask = ~((unsigned)-1 << 31 - 0);
    print_bits(mask);
    return xsrl ;
}

int main()
{
    int original = -1;

    printf("Init ");
    print_bits(original);
    print_bits(sra(-1, 1));
}