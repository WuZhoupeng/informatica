#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

unsigned int M[3][15];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* maxValue (void* args);

int main (void) {
    srand(time(NULL));

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 15; ++k) {
            M[i][k] = (unsigned int) rand() % 100;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 15; ++k) {
            printf("%u ", M[i][k]);
        }

        printf("\n");
    }

    pthread_t th1;
    pthread_t th2;
    pthread_t th3;

    unsigned int* res1;
    unsigned int* res2;
    unsigned int* res3;
    unsigned int absolute_value = 0;

    if (pthread_create(&th1, NULL, maxValue, (void*)(intptr_t) 0) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, maxValue, (void*)(intptr_t) 1) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, maxValue, (void*)(intptr_t) 2) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, (void**) &res1);
    pthread_join(th2, (void**) &res2);
    pthread_join(th3, (void**) &res3);

    printf("Max in th1: %u\n", *res1);
    printf("Max in th2: %u\n", *res2);
    printf("Max in th3: %u\n", *res3);

    if (*res1 > *res2) {
        if (*res1 > *res3) absolute_value = *res1;
        else absolute_value = *res3;
    }
    else {
        if (*res2 > *res3) absolute_value = *res2;
        else absolute_value = *res3;
    }

    printf("MAX: %u\n", absolute_value);

    return 0;
}

void* maxValue (void* args) {
    intptr_t arg = (intptr_t) args;
    unsigned int* result = malloc(sizeof(unsigned int));
    *result = 0;

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 15; ++i) {
        if (*result < M[arg][i]) *result = M[arg][i];
    }
    pthread_mutex_unlock(&mutex);

    return (void*) result;
}