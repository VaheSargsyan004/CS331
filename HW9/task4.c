#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numbers[] = {1, 2, 3, 4, 5};

void* calculate_square(void* arg) {
    int num = *((int*)arg);
    printf("Square of %d is %d\n", num, num * num);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int i;

    for(i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, calculate_square, &numbers[i]) != 0) {
            fprintf(stderr, "Failed to create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < 5; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have finished their execution!!!\n");
    return 0;
}

