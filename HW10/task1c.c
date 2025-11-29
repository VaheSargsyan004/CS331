#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4         // Number of threads
#define M 1000000   // Number of increments

long long counter = 0; // Global counter
pthread_spinlock_t spinlock;

void* increment_spinlock(void* arg) {
    for (long i = 0; i < M; i++) {
        pthread_spin_lock(&spinlock);
        counter++;
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    pthread_spin_init(&spinlock, 0);

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, increment_spinlock, NULL);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Version C - Spinlock\n");
    printf("Expected: %lld\n", (long long)N * M);
    printf("Actual:   %lld\n", counter);

    pthread_spin_destroy(&spinlock);
    return 0;
}

