#define _GNU_SOURCE // Enable GNU extensions
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

void* print_numbers(void* arg) {
    int thread_id = *((int*)arg);
    for(int i = 1; i <= 5; i++) {
        printf("Thread %d: %d\n", thread_id, i);
    }
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3];

    for(int i = 0; i < 3; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, print_numbers, &thread_ids[i]) != 0) {
            fprintf(stderr, "Failed to create thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have finished execution!!!\n");
    return 0;
}

