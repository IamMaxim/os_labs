#include <stdio.h>


int main() {
    int n;
    printf("Enter N: ");
    scanf("%i", &n);
    printf("Creating array of %i integers\n");

    int *arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    printf("Done. Deallocating.\n");
    free(arr);

    return 0;
}
