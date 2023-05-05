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


void dual_pivot_quick_sort(int left, int right) {
    if (left < right) {
        if (comparison(arr[left],arr[right])) {
            swap(&arr[left], &arr[right]);
        }
        int p = arr[left];
        int q = arr[right];

        int l = left + 1;
        int g = right - 1;
        int k = l;

        while (comparison(g+1, k)) {
            if (comparison(p, arr[k])) {
                swap(&arr[k], &arr[l]);
                l++;
            } else if (comparison(arr[k]+1, q)) {
                while (comparison(arr[g], q) && comparison(g, k)) {
                    g--;
                }
                swap(&arr[k], &arr[g]);
                g--;
                if (comparison(p, arr[k])) {
                    swap(&arr[k], &arr[l]);
                    l++;
                }
            }
            k++;
        }
        l--;
        g++;

        swap(&arr[left], &arr[l]);
        swap(&arr[right], &arr[g]);

        print_arr();

        dual_pivot_quick_sort(left, l - 1);
        dual_pivot_quick_sort(l + 1, g - 1);
        dual_pivot_quick_sort(g + 1, right);
    }
}

int main(int argc, char *argv[]){

    get_array();

    dual_pivot_quick_sort(0, n-1);

    print_result();
//    print_count();
    return 0;
}