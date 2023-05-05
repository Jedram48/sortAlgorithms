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
    return a >= b;
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
    printf("%d/%d", comp_count, swap_count);
}

int partition(int array[], int p, int q){
    int pivot = array[p];
    int i = p;

    for(int j = p+1; j<=q; j++){
        if(comparison(pivot, array[j])){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i], &array[p]);
    return i;
}

void quick_sort(int array[], int low, int high){
    if (low < high) {
        int pi = partition(arr, low, high);

        if(n<40){print_arr();}

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[]){

    get_array();

    quick_sort(arr, 0, n-1);

    print_result();
//    print_count();
    return 0;
}