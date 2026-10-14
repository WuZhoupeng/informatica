#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int MAX_PARCHEGGIO = 5;
int posti_occupati = 0;
sem_t sem;

void* entra (void* args);
void* esci (void* args);

int main (void) {
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;
    pthread_t th6;
    pthread_t th7;
    pthread_t th8;

    if (sem_init(&sem, 0, 1) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, entra, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, entra, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, entra, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th4, NULL, entra, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th5, NULL, esci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th6, NULL, esci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th7, NULL, esci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th8, NULL, esci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    pthread_join(th5, NULL);
    pthread_join(th6, NULL);
    pthread_join(th7, NULL);
    pthread_join(th8, NULL);

    return 0;
}

void* entra (void* args) {
    for (int i = 0; i < MAX_PARCHEGGIO; ++i) {
        sem_wait(&sem);

        if (posti_occupati >= MAX_PARCHEGGIO) {
            printf("Parcheggio pieno!!!\n");
        }
        else {
            posti_occupati++;
            printf("Auto entrato (%d)\n", posti_occupati);
        }

        sem_post(&sem);

        usleep(400000);
    }

    return NULL;
}

void* esci (void* args) {
    for (int i = 0; i < MAX_PARCHEGGIO; ++i) {
        sem_wait(&sem);

        if (posti_occupati <= 0) {
            printf("Parcheggio vuoto!!!\n");
        }
        else {
            posti_occupati--;
            printf("Auto uscito (%d)\n", posti_occupati);
        }

        sem_post(&sem);

        usleep(400000);
    }

    return NULL;
}