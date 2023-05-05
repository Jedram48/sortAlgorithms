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

    printf("Ciag jest posortowany: %s", check() ? "true" : "false");
}

void print_count(){
    printf("\n%d/%d", comp_count, swap_count);
}

int median_of_three(int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid]) {
        swap(&arr[left], &arr[mid]);
    }
    if (arr[left] > arr[right]) {
        swap(&arr[left], &arr[right]);
    }
    if (arr[mid] > arr[right]) {
        swap(&arr[mid], &arr[right]);
    }
    return mid;
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

int partition( int p, int q){
    int pivot = median_of_three(p, q);
    int i = p;

    for(int j = p+1; j<=q; j++){
        if(comparison(pivot, arr[j])){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i], &arr[p]);
    return i;
}

void hybrid_sort(int left, int right){
    const int threshold = 10;
    if (right - left + 1 <= threshold) {
        insertion_sort(left, right);
    } else {
        int p = partition(left, right);
        hybrid_sort(left, p);
        hybrid_sort(p + 1, right);
        merge(left, p, right);
    }
}

void optimized_hybrid_sort(int left, int right){
    const int threshold = 10;
    if (right - left + 1 <= threshold) {
        insertion_sort(left, right);
    } else {
        int p = partition(left, right);
        if (p - left < right - p){
            optimized_hybrid_sort(left, p);
            optimized_hybrid_sort(p + 1, right);
        } else {
            optimized_hybrid_sort(p + 1, right);
            optimized_hybrid_sort(left, p);
        }
        merge(left, p, right);
    }
}

int main(int argc, char *argv[]){

    get_array();

    hybrid_sort(0, n);

    print_result();
    print_count();
    
    return 0;
}