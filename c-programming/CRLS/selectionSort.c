
int* selectionSort(int *a, int n) {
    for (int i = 0; i < n; i++)
    {
        int idxHolder = i;
        int smaller = *(a + i);
        for (int j = i + 1; j < n; j++)
        {
            if (*(a + j) < smaller) {
                idxHolder = j;
                smaller = *(a + j);
            }
        }
        int holder = *(a + idxHolder);
        *(a + idxHolder) = *(a + i);
        *(a + i) = holder;
    }
    return a;
    
}

int main() {
    int a[9] = { 9,8,7,6,5,4,3,2,1};
    selectionSort(&a, 9);
    for (int i = 0; i < 9; i++)
    {
        printf("%d", a[i]);
    }
    
}