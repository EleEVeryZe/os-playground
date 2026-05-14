#include <string.h>
/*
Write a procedure is_little_endian that will return 1 when compiled and run
on a little-endian machine, and will return 0 when compiled and run on a bigendian machine. This program should run on any machine, regardless of its word
size.
*/
typedef unsigned char *bytePointer;

int isLittleEndian()
{
    short isLittleEndien = 0;
    int a = 0x12345641;
    bytePointer by = (bytePointer)&a;
    if (by[0] == 'A')
    {
        printf("Is little endian\n");
        isLittleEndien = 1;
    }

    printf("SizeOfInt: %d\n", sizeof(int));
    int i = 0;
    while (i < sizeof(int))
    {
        printf("In Decimal: %d\n", by[i]);
        printf("In Hexadecimal: %.2x\n", by[i]);
        i++;
    }
    return isLittleEndien;
}

int main()
{
    isLittleEndian();
}