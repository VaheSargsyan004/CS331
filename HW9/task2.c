#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[] = {1, 2, 3, 4, 5, 6};
int sum_1 = 0, sum_2 = 0;

void* first_half(void* arg) {
    for(int i = 0; i < 3; i++) {
        sum_1 += arr[i];
    }
    printf("Sum of first half: %d\n", sum_1);
    return NULL;
}

void* second_half(void* arg) {
    for(int i = 3; i < 6; i++) {
        sum_2 += arr[i];
    }
    printf("Sum of second half: %d\n", sum_2);
    return NULL;
}

int main() {
    pthread_t thread_1, thread_2;

    if (pthread_create(&thread_1, NULL, first_half, NULL) != 0) {
        fprintf(stderr, "Failed to create first_half thread\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_2, NULL, second_half, NULL) != 0) {
        fprintf(stderr, "Failed to create second_half thread\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread_1, NULL) != 0) {
        fprintf(stderr, "Failed to join first_half thread\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread_2, NULL) != 0) {
        fprintf(stderr, "Failed to join second_half thread\n");
        exit(EXIT_FAILURE);
    }

    printf("All threads have finished their execution!!!\n");

    return 0;
}

