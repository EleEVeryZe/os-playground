/*
Write a C expression that will yield a word consisting of the least significant byte of
x and the remaining bytes of y. For operands x=0x89ABCDEF and y=0x76543210,
this would give 0x765432EF.
*/
int main() {
    int x = 0x89ABCDEF;
    int y = 0x76543210;
    int z = (x & 0xff) | (y & 0xffffff00);
    return z;
    //printf("New number in hex: 0x%.2x\n", ((x & 0xff) | (y & 0xffffff00)));
}