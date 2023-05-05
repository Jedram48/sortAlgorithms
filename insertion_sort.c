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

int main(int argc, char *argv[]){

    get_array();

    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;

        while(j>=0 && comparison(arr[j], key)){
            swap(&arr[j+1], arr[j]);
            j--;
        }
        if(j+1!=i){swap(&arr[j+1], key);}
        if(n < 40){print_arr();}
    }

    print_result();
//    print_count();
    
    return 0;
}