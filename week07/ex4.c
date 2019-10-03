#include <stdio.h>
#include <stdlib.h>

void *realloc1(void *ptr, size_t old_size, size_t size) {
    // Create new data allocation if no previous one was passed.
    if (ptr == NULL)
        return malloc(size);

    // Free previous data allocation if new size if 0.
    if (size == NULL) {
        free(ptr);
        return 0;
    }

    void *newData = malloc(size);

    // Copy old data to the new location
    int minSize = size < old_size ? size : old_size;
    for (int i = 0; i < minSize; i++) {
        ((int *) newData)[i] = ((int *) ptr)[i];
    }

    free(ptr);
    return newData;
}


int main() {
    int *data;
    int n1 = 4;
    data = realloc1(NULL, 0, n1);
    for (int i = 0; i < n1; i++) {
        data[i] = i;
        printf("%i ", data[i]);
    }
    printf("\n");

    int n2 = 6;
    data = realloc1(data, n1, n2);
    
    for (int i = 0; i < n2; i++) {
        printf("%i ", data[i]);
    }
    printf("\n");
    realloc1(data, n2, 0);

    printf("Bye.\n");

    return 0;
}
