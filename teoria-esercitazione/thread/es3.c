#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

intptr_t counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment (void* args);

int main (void) {
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;

    intptr_t* res1;
    intptr_t* res2;
    intptr_t* res3;
    intptr_t* res4;
    intptr_t* res5;

    if (pthread_create(&th1, NULL, increment, (void*)(intptr_t) 0) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }
    if (pthread_create(&th2, NULL, increment, (void*)(intptr_t) 1) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }
    if (pthread_create(&th3, NULL, increment, (void*)(intptr_t) 2) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }
    if (pthread_create(&th4, NULL, increment, (void*)(intptr_t) 3) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }
    if (pthread_create(&th5, NULL, increment, (void*)(intptr_t) 4) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, (void**) &res1);
    pthread_join(th2, (void**) &res2);
    pthread_join(th3, (void**) &res3);
    pthread_join(th4, (void**) &res4);
    pthread_join(th5, (void**) &res5);

    printf("Thread 1: %lld\n", *res1);
    printf("Thread 2: %lld\n", *res2);
    printf("Thread 3: %lld\n", *res3);
    printf("Thread 4: %lld\n", *res4);
    printf("Thread 5: %lld\n", *res5);
    printf("Global count: %lld\n", counter);

    return 0;
}

void* increment (void* args) {
    intptr_t arg = (intptr_t) args;
    intptr_t* res = malloc(sizeof(intptr_t));

    *res = (arg + 1) * 100;

    pthread_mutex_lock(&mutex);
    counter += *res;
    pthread_mutex_unlock(&mutex);

    return (void*) res;
}