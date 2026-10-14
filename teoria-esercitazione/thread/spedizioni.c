#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

intptr_t spedizioni[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
const intptr_t intervallo = 10;
intptr_t total = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* elaborate (void* args);

int main (void) {
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;

    intptr_t* res1;
    intptr_t* res2;
    intptr_t* res3;

    if (pthread_create(&th1, NULL, elaborate, (void*)(intptr_t) 0) != 0) {
        printf("Errore nella creazione del thread\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, elaborate, (void*)(intptr_t) 1) != 0) {
        printf("Errore nella creazione del thread\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, elaborate, (void*)(intptr_t) 2) != 0) {
        printf("Errore nella creazione del thread\n");

        return 1;
    }

    pthread_join(th1, (void**) &res1);
    pthread_join(th1, (void**) &res2);
    pthread_join(th1, (void**) &res3);

    printf("Thread 1 spedizioni: %lld\n", *res1);
    printf("Thread 2 spedizioni: %lld\n", *res2);
    printf("Thread 3 spedizioni: %lld\n", *res3);
    printf("Totali spedizioni: %lld\n", total);

    return 0;
}

void* elaborate (void* args) {
    intptr_t arg = (intptr_t) args;
    intptr_t* res = malloc(sizeof(intptr_t));

    pthread_mutex_lock(&mutex);
    for (intptr_t i = intervallo * arg; i < intervallo * (arg + 1); ++i) {
        total += spedizioni[i];
        *res += spedizioni[i];
    }
    pthread_mutex_unlock(&mutex);

    return (void*) res;
}