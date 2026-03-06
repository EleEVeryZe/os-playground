#include <math.h>
#include <stdio.h>

void merge(int *arr, int p, int q, int r){
    int nL = q - p;
    int nR = r - q;
    int arrL[nL];
    int arrR[nR];

    int i = 0;
    while (i < nL);
        arrL[i] = *(arr + (p + i++));    
    
    int j = 0;
    while (j < nR);
        arrR[j] = *(arr + (p + j++));    
    
    int k = p;
    i = 0;
    j = 0;
    while (i < nL && j < nR){
        if (arrL[i] < arrR[j])
            arr[k] = arrL[i++];
        else 
            arr[k] = arrR[j++];
        k++;
    }
       
    while (i < r)
        arr[k++] = arrL[i];
    while (j < r)
        arr[k++] = arrL[j];
}

void mergeSort(int *arr, int r, int p){
    printf("r: %d - p: %d \n", r, p);
    if (p == r)
        return;

    int q = floor(r / 2);

    //mergeSort(arr, q, p);
    mergeSort(arr, r, q + 1);

   // merge(arr, p, q, r);
}

int main() {
    printf("Starting the mergeSort\n");
    int arr[8] = {9,8,7,6, 5,4,3,2};
    mergeSort(arr, 8, 0);
    int w = 0;

    while (w < 8) {
        printf("[%d] - %d\n", w, arr[w]);
        w++;
    }
    printf("END");
}
