#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int comp_count = 0;
int swap_count = 0;
int n;
int *arr;

void print_arr(int array[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool comparison(int a, int b){
    comp_count++;
    return a > b;
}

void swap(int *ptr, int key){
    *ptr = key;
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
    print_arr(arr, n);
}

void print_result(){
    printf("Tablica po sortowaniu: ");
    print_arr(arr, n);

    printf("Liczba porownan: %d\n", comp_count);
    printf("Liczba przestawien: %d\n", swap_count);

    printf("Ciag jest posortowany: %s\n", check() ? "true" : "false");
}

void print_count(){
    printf("%d/%d", comp_count, swap_count);
}

int* merge(int a[], int b[], int size_a, int size_b){
    int* merged = (int*) malloc(sizeof(int) * (size_a + size_b));
    int i = 0, j = 0, k = 0;

    while (i < size_a && j < size_b) {
        if (comparison(b[j], a[i])) {
            swap(&merged[k++], a[i++]);
        } else {
            swap(&merged[k++], b[j++]);
        }
    }

    while (i < size_a) {
        swap(&merged[k++], a[i++]);
    }

    while (j < size_b) {
        swap(&merged[k++], b[j++]);
    }

    return merged;
}

int* merge_sort(int array[], int size){
    if(size == 1){return array;}
    int size1 = size/2, size2 = size-(int)(size/2), k = 0, l = 0;
    int arr1[size1], arr2[size2];

    for(int i = 0; i<size; i++){
        if(i<size1){
            arr1[k++] = array[i];
        }
        else{
            arr2[l++] = array[i];
        }
    }

    int* A = merge_sort(arr1, size1);
    int* B = merge_sort(arr2, size2);
    int* result = merge(A, B, size1, size2);
    if(n<40){print_arr(result, size);}
    return result;
}

int main(int argc, char *argv[]){

    get_array();

    arr = merge_sort(arr, n);

    print_result();
//    print_count();
    return 0;
}