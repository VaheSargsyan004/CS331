#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10  // Number of print job threads
#define K 3   // Number of printers

sem_t printers;
pthread_mutex_t counter_mutex;
int printing_count = 0;

void* print_job(void* arg) {
    int id = *(int*)arg;

    sem_wait(&printers); // Acquire a printer

    pthread_mutex_lock(&counter_mutex);
    printing_count++;
    printf("Thread %d is printing (currently %d threads printing)\n", id, printing_count);
    pthread_mutex_unlock(&counter_mutex);

    usleep(500000); // Simulate printing for 0.5s

    pthread_mutex_lock(&counter_mutex);
    printing_count--;
    pthread_mutex_unlock(&counter_mutex);

    sem_post(&printers); // Release printer

    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    sem_init(&printers, 0, K);
    pthread_mutex_init(&counter_mutex, NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, print_job, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&printers);
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}

