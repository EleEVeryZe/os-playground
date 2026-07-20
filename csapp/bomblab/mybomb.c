int sum(int s, int j) {
    return s + j;
}
int main() {
    int s = 16;
    int j = 32;
    int ac = 0;
    while (ac < 96)
        ac += sum(s, j);
    return ac;
    //printf("Sum: %d", sum(s, j));
}