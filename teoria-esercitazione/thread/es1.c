#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int totale = 0;

void* counter (void* args);

int main () {
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;

    int* res1;
    int* res2;
    int* res3;
    int* res4;
    int* res5;

    pthread_create(&th1, NULL, counter, (void*) 3);
    pthread_create(&th2, NULL, counter, (void*) 4);
    pthread_create(&th3, NULL, counter, (void*) 5);
    pthread_create(&th4, NULL, counter, (void*) 6);
    pthread_create(&th5, NULL, counter, (void*) 7);

    pthread_join(th1, (void**) &res1);
    pthread_join(th2, (void**) &res2);
    pthread_join(th3, (void**) &res3);
    pthread_join(th4, (void**) &res4);
    pthread_join(th5, (void**) &res5);

    printf("Thread 1: %d\n", *res1);
    printf("Thread 2: %d\n", *res2);
    printf("Thread 3: %d\n", *res3);
    printf("Thread 4: %d\n", *res4);
    printf("Thread 5: %d\n", *res5);
    printf("Totale: %d\n", totale);

    return 0;
}

void* counter (void* args) {
    int arg = (int)(long) args;
    int result = 0;

    for (int i = 1; i < arg; ++i) {
        result += i;
    }

    pthread_mutex_lock(&mutex);
    totale += result;
    pthread_mutex_unlock(&mutex);

    int* result_p = malloc(sizeof(int));
    *result_p = result;

    return (void*) result_p;
}
