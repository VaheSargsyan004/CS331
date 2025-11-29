#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10  // Number of iterations

sem_t semA, semB, semC;
pthread_mutex_t print_mutex; // optional, for cleaner printing

void* thread_A(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semA); // Wait for its turn
        pthread_mutex_lock(&print_mutex);
        printf("Thread A: A %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semB); // Signal B
    }
    return NULL;
}

void* thread_B(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semB); // Wait for its turn
        pthread_mutex_lock(&print_mutex);
        printf("Thread B: B %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semC); // Signal C
    }
    return NULL;
}

void* thread_C(void* arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semC); // Wait for its turn
        pthread_mutex_lock(&print_mutex);
        printf("Thread C: C %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semA); // Signal A for next iteration
    }
    return NULL;
}

int main() {
    pthread_t tA, tB, tC;

    // Initialize semaphores
    sem_init(&semA, 0, 1); // A starts first
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    pthread_mutex_init(&print_mutex, NULL);

    // Create threads
    pthread_create(&tA, NULL, thread_A, NULL);
    pthread_create(&tB, NULL, thread_B, NULL);
    pthread_create(&tC, NULL, thread_C, NULL);

    // Join threads
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}

