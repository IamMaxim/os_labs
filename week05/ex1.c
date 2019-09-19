#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 20

void *thread_func(void *args) {
    int index = ((int *) args)[0];
    printf("I'm inside the thread %d\n", index);

    return NULL;
}

int main() {
    printf("Gonna create some threads...\n");

    // Create some threads in the loop
    for (int i = 0; i < N; i++) {
        printf("Creating thread %d\n", i);
        pthread_t thread;
        // Allocate space in the heap, so it will be individual for each thread
        int *args = malloc(sizeof(int));
        args[0] = i;
        // Start the thread
        pthread_create(&thread, NULL, &thread_func, args);

        // Join the thread, so executing blocks until new thread completes its job
        pthread_join(thread, NULL);
    }
}

