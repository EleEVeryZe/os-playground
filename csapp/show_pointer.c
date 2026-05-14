#include <stdio.h>
typedef unsigned char *byte_pointer;

void showBytes(byte_pointer start, size_t len)
{
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void showInt(int x)
{
    showBytes((byte_pointer)&x, sizeof(int));
}

void showFloat(float x)
{
    showBytes((byte_pointer)&x, sizeof(float));
}

void showShort(short x)
{
    showBytes((byte_pointer)&x, sizeof(short));
}

void showLong(long x)
{
    showBytes((byte_pointer)&x, sizeof(long));
}

void showDouble(double x)
{
    showBytes((byte_pointer)&x, sizeof(double));
}

void showPointer(void *x)
{
    showBytes((byte_pointer)&x, sizeof(void *));
}

int main()
{
    // Ex2.55
    int hex = 0x12345678;
    byte_pointer ap = (byte_pointer)&hex;
    showBytes(ap, sizeof(hex));

    // Ex2.56 Try running the code for show_bytes for different sample values.
    int hex2 = 0x64;
    byte_pointer ap2 = (byte_pointer)&hex2;
    showBytes(ap2, sizeof(hex2));

    /*
        2.57
        Write procedures show_short, show_long, and show_double that print the byte
        representations of C objects of types short, long, and double, respectively. Try
        these out on several machines.
    */
    printf("\nshowShort: ");
    short pequeno = 100;
    showShort(pequeno);
    printf("\n");

    printf("\nshowLong: ");
    long grande = 100;
    showLong(grande);
    printf("\n");

    printf("\nshowDouble: ");
    double duplo = 100;
    showDouble(duplo);
    printf("\n");
}
