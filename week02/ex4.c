#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

int main() {
    printf("Enter 2 ints:\n> ");
    int a, b;
    scanf("%i %i", &a, &b);

    swap(&a, &b);

    printf("swapped! %i %i\n", a, b);

    return 0;
}