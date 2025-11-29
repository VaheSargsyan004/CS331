#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4         // Number of threads
#define M 1000000   // Number of increments

long long counter = 0; // Global counter
void* increment_no_sync(void* arg) {
    for (long i = 0; i < M; i++) {
        counter++; // Race condition possible here
    }
    return NULL;
}

int main() {
    pthread_t threads[N];

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, increment_no_sync, NULL);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Version A - No Synchronization\n");
    printf("Expected: %lld\n", (long long)N * M);
    printf("Actual:   %lld\n", counter);

    return 0;
}

