#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ELABORATION_DATA 100

pthread_mutex_t mutex;
pthread_cond_t cond;

int quantity_oil = 0;
int i = 0, k = 0;

void* producer (void* args);
void* consumer (void* args);

int main (void) {
    srand(time(NULL));

    pthread_t th1;
    pthread_t th2;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Errore nella creazione del mutex!\n");

        return 1;
    }

    if (pthread_cond_init(&cond, NULL) != 0) {
        printf("Errore nella creazione del thread condizione!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, producer, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, consumer, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

void* producer (void* args) {
    while (i < MAX_ELABORATION_DATA) {
        pthread_mutex_lock(&mutex);

        int quantity_to_fill = 1 + rand() % 75;
        printf("Caricato %d litri di benzina!\n", quantity_to_fill);
        quantity_oil += quantity_to_fill;
        printf("[INFO] Totale benzina attuale: %d\n", quantity_oil);

        pthread_cond_signal(&cond);
        ++i;
        pthread_mutex_unlock(&mutex);

        usleep(50000);
    }

    return NULL;
}

void* consumer (void* args) {
    while (k < MAX_ELABORATION_DATA) {
        pthread_mutex_lock(&mutex);

        while (quantity_oil < 50) {
            printf("Attendo...\n");

            pthread_cond_wait(&cond, &mutex);
        }

        int quantity_to_consumer = 1 + rand() % 35;
        printf("Cliente ha consumato %d litri di benzina!\n", quantity_to_consumer);
        quantity_oil -= quantity_to_consumer;
        printf("[INFO] Totale benzina attuale: %d\n", quantity_oil);
        ++k;

        pthread_mutex_unlock(&mutex);

        usleep(50000);
    }

    return NULL;
}