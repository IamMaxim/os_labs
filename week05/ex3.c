#include <stdio.h>
#include <pthread.h>
#include <zconf.h>

#define BUFFER_SIZE 8

pthread_cond_t wait_obj;
int buffer[BUFFER_SIZE];
int cur_element_count = 0;

void add_element(int n) {
    buffer[cur_element_count++] = n;
}

int fetch_element() {
    return buffer[--cur_element_count];
}

// Function for the producer thread
void *producer_func(void *args) {
    int counter = 0;
    time_t last_print = 0;

    while (1) {
        // Lock
        if (cur_element_count == BUFFER_SIZE) {
            pthread_cond_wait(&wait_obj, NULL);
        }

        add_element(counter);

        // Print not more than 1 time per minute
        if (time(NULL) - last_print < 60) {
            last_print = time(NULL);
            printf("Added element %d\n", counter);
        }

        pthread_cond_signal(&wait_obj);

        counter++;
    }

    return NULL;
}

void *consumer_func(void *args) {
    time_t last_print = 0;

    while (1) {
        if (cur_element_count == 0) {
            pthread_cond_wait(&wait_obj, NULL);
        }

        int n = fetch_element();

        // Print not more than 1 time per minute
        if (time(NULL) - last_print < 60) {
            last_print = time(NULL);
            printf("Fetched element %d\n", n);
        }
        pthread_cond_signal(&wait_obj);
    }

    return NULL;
}

int main() {
    pthread_cond_init(&wait_obj, NULL);

    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producer_func, NULL);
    pthread_create(&consumer, NULL, consumer_func, NULL);

    while (1) {
        sleep(100000000);
    }
}
