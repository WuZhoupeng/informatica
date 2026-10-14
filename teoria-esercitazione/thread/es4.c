#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

intptr_t saldo = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* preleva (void* args);

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

    if (pthread_create(&th1, NULL, preleva, (void*)(intptr_t) 100) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, preleva, (void*)(intptr_t) 100) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, preleva, (void*)(intptr_t) 100) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th4, NULL, preleva, (void*)(intptr_t) 100) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th5, NULL, preleva, (void*)(intptr_t) 100) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, (void**) &res1);
    pthread_join(th2, (void**) &res2);
    pthread_join(th3, (void**) &res3);
    pthread_join(th4, (void**) &res4);
    pthread_join(th5, (void**) &res5);

    if (*res1 == 1) printf("Thread 1: prelievo riuscito\n");
    else printf("Thread 1: prelievo non riuscito\n");

    if (*res2 == 1) printf("Thread 2: prelievo riuscito\n");
    else printf("Thread 2: prelievo non riuscito\n");

    if (*res3 == 1) printf("Thread 3: prelievo riuscito\n");
    else printf("Thread 3: prelievo non riuscito\n");

    if (*res4 == 1) printf("Thread 4: prelievo riuscito\n");
    else printf("Thread 4: prelievo non riuscito\n");

    if (*res5 == 1) printf("Thread 5: prelievo riuscito\n");
    else printf("Thread 5: prelievo non riuscito\n");

    printf("Saldo totale: %lld", saldo);

    return 0;
}


void* preleva (void* args) {
    intptr_t arg = (intptr_t) args;
    intptr_t* res = malloc(sizeof(intptr_t));

    if (saldo < arg) {
        *res = 0;

        return (void*) res;
    }

    pthread_mutex_lock(&mutex);
    saldo -= arg;
    pthread_mutex_unlock(&mutex);
    *res = 1;


    return (void*) res;
}