/*
Suppose we number the bytes in a w-bit word from 0 (least significant) to w/8 − 1
(most significant). Write code for the following C function, which will return an
unsigned value in which byte i of argument x has been replaced by byte b:

unsigned replace_byte (unsigned x, int i, unsigned char b);

Here are some examples showing how the function should work:
    replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
    replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
*/

int replace_byte(unsigned x, int i, unsigned char b)
{
    unsigned mask = 0xff << (8 * i);
    return (x & ~mask) | (b << (8 * i));
}

int main()
{
    printf("%d\n", sizeof(int));
    printf("Hex: 0x%.2x == 0x12AB5678\n", replace_byte(0x12345678, 2, 0xAB));
    printf("Hex: 0x%.2x == 0x125678AB\n", replace_byte(0x12345678, 0, 0xAB));
}