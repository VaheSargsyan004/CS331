#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define NUM_DEPOSIT 4
#define NUM_WITHDRAW 4
#define OPERATIONS 400

long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spinlock;

int use_mutex = 1;  // 1 = mutex, 0 = spinlock
int long_cs = 0;    // 0 = short critical section, 1 = long

void* deposit(void* arg) {
    for (long i = 0; i < OPERATIONS; i++) {
        if (use_mutex) pthread_mutex_lock(&mutex);
        else pthread_spin_lock(&spinlock);

        balance++;
        if (long_cs) usleep(100);

        if (use_mutex) pthread_mutex_unlock(&mutex);
        else pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (long i = 0; i < OPERATIONS; i++) {
        if (use_mutex) pthread_mutex_lock(&mutex);
        else pthread_spin_lock(&spinlock);

        balance--;
        if (long_cs) usleep(100);

        if (use_mutex) pthread_mutex_unlock(&mutex);
        else pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [mutex|spin] [short|long]\n", argv[0]);
        return 1;
    }

    use_mutex = strcmp(argv[1], "mutex") == 0 ? 1 : 0;
    long_cs = strcmp(argv[2], "long") == 0 ? 1 : 0;

    if (use_mutex) pthread_mutex_init(&mutex, NULL);
    else pthread_spin_init(&spinlock, 0);

    pthread_t deposits[NUM_DEPOSIT], withdraws[NUM_WITHDRAW];
    clock_t start = clock();

    for (int i = 0; i < NUM_DEPOSIT; i++)
        pthread_create(&deposits[i], NULL, deposit, NULL);
    for (int i = 0; i < NUM_WITHDRAW; i++)
        pthread_create(&withdraws[i], NULL, withdraw, NULL);

    for (int i = 0; i < NUM_DEPOSIT; i++)
        pthread_join(deposits[i], NULL);
    for (int i = 0; i < NUM_WITHDRAW; i++)
        pthread_join(withdraws[i], NULL);

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Final balance: %lld\n", balance);
    printf("Elapsed time: %.4f seconds\n", elapsed);

    if (use_mutex) pthread_mutex_destroy(&mutex);
    else pthread_spin_destroy(&spinlock);

    return 0;
}

