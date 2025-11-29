#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
#define P 2
#define C 2
#define K 100000

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;
int total_items = P * K;
int consumed_count = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void* producer(void* arg) {
    for (int i = 0; i < K; i++) {
        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_mutex);

        buffer[in_pos] = i; // storing item, value does not matter
        in_pos = (in_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);

        if (consumed_count >= total_items) {
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&full_slots); // unblock other consumers
            break;
        }

        int item = buffer[out_pos]; // reading item
        out_pos = (out_pos + 1) % BUFFER_SIZE;
        consumed_count++;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);
    }
    return NULL;
}

int main() {
    pthread_t producers[P], consumers[C];

    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    for (int i = 0; i < P; i++)
        pthread_create(&producers[i], NULL, producer, NULL);
    for (int i = 0; i < C; i++)
        pthread_create(&consumers[i], NULL, consumer, NULL);

    for (int i = 0; i < P; i++) pthread_join(producers[i], NULL);
    for (int i = 0; i < C; i++) sem_post(&full_slots); // unblock consumers
    for (int i = 0; i < C; i++) pthread_join(consumers[i], NULL);

    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    printf("All %d items produced and consumed.\n", consumed_count);
    return 0;
}

