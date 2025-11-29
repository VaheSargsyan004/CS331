#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4         // Number of threads
#define M 1000000   // Number of increments

long long counter = 0; // Global counter
pthread_mutex_t lock;

void* increment_mutex(void* arg) {
    for (long i = 0; i < M; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, increment_mutex, NULL);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Version B - Mutex\n");
    printf("Expected: %lld\n", (long long)N * M);
    printf("Actual:   %lld\n", counter);

    pthread_mutex_destroy(&lock);
    return 0;
}

