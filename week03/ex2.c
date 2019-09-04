#include <stdio.h>


// Swaps two integers. Nothing else.
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sorts the elements of a given array with size len
// using bubble sort algorithm.
void bubble_sort(int *arr, int len) {
    // First loop iterates over not-yet-sorted region of the array
    for (int i = 0; i < len - 1; i++) {
        // Second loop does actually swap items which are in the wrong order
        for (int j = i; j < len - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are not in increasing order
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


// Prints the given array of integers, separating elements with comma
void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);

        if (i != size - 1)
            printf(", ");
    }
}

int main() {
    int arr[] = {1, 6, 3, 8, 3};
    
    printf("Before sort: ");
    print_array(arr, 5);
    printf("\n");

    bubble_sort(arr, 5);

    printf("After sort:  ");
    print_array(arr, 5);
    printf("\n");

    return 0;
}