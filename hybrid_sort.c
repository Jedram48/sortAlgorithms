#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int comp_count = 0;
int swap_count = 0;
int n;
int *arr;

void print_arr(){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

bool comparison(int a, int b){
    comp_count++;
    return a > b;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

bool check(){
    for(int i = 1; i < n; i++){
        if(arr[i] < arr[i-1]){return false;}
    }
    return true;
}

void get_array(){
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    arr = a;

    printf("Tablica przed sortowaniem: ");
    print_arr();
}

void print_result(){
    printf("Tablica po sortowaniu: ");
    print_arr();

    printf("Liczba porownan: %d\n", comp_count);
    printf("Liczba przestawien: %d\n", swap_count);

    printf("Ciag jest posortowany: %s\n", check() ? "true" : "false");
}

void print_count(){
    printf("\n%d/%d", comp_count, swap_count);
}

void insertion_sort(int left, int right){
    for(int i = left+1; i <= right; i++){
        int key = arr[i];
        int j = i - 1;

        while(j>=left && comparison(arr[j], key)){
            swap(&arr[j+1], &arr[j]);
            j--;
        }
        if(j+1!=i){swap(&arr[j+1], &key);}
    }
}

int merge(int left, int mid, int right){
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int L[size1], R[size2];

    for(int i = 0; i < size1; i++){
        L[i] = arr[left + i];
    }
    for(int j = 0; j < size2; j++){
        R[j] = arr[mid + j + 1];
    }


    int i = 0, j = 0, k = left;
    while(i < size1 && j < size2){
        if(comparison(R[j]+1, L[i])){
            swap(&arr[k++], &L[i++]);
        } else {
            swap(&arr[k++], &R[j++]);
        }
    }    

    while (i < size1) {
        swap(&arr[k++], &L[i++]);
    }

    while (j < size2) {
        swap(&arr[k++], &R[j++]);
    }
}

void hybrid_sort(int left, int right){
    if (right - left + 1 <= 5) {
        insertion_sort(left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    hybrid_sort(left, mid);
    hybrid_sort(mid + 1, right);
    if(n<40){print_arr();}
    merge(left, mid, right);
}

int main(int argc, char *argv[]){

    get_array();

    hybrid_sort(0, n-1);

    print_result();
//    print_count();
    
    return 0;
}