#define _GNU_SOURCE // Enable GNU extensions
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void* arg) {
    pthread_t sys_tid = pthread_self();
    
    long thread_id = (long)arg;
    
    printf("Thread %ld is running (System ID: %lu)\n", 
           thread_id, (unsigned long)sys_tid);
    
    return NULL;
};

int main() {
    pthread_t threads[3];

    for(long i = 0; i < 3; i++) {
       if(pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0){
          fprintf(stderr, "Failed to create thread %ld\n", i);
          exit(EXIT_FAILURE);
       }
    };

    for(int i = 0; i < 3; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
           fprintf(stderr, "Failed to join thread %d\n", i);
           exit(EXIT_FAILURE);
	}
    };

    printf("All threads have finished their execution!!!\n");

    return 0;
}

