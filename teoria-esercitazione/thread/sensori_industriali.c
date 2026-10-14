#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ELABORATION_DATA 1000

sem_t producer_sem;
sem_t consumer_sem;

const char tipi_di_sensori[3][20] = {
    "temperatura",
    "pressione",
    "umidita"
};

char queue_sensori[10][20] = {};
int i = 0;
int k = 0;

int freePlace ();
int busyPlace ();
void* producer (void* args);
void* consumer (void* args);

int main (void) {
    srand(time(NULL));

    pthread_t th1;
    pthread_t th2;

    if (sem_init(&producer_sem, 0, 10) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&consumer_sem, 0, 0) != 0) {
        printf("Errore nella creazione del semaforo!\n");

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

    sem_destroy(&producer_sem);
    sem_destroy(&consumer_sem);

    return 0;
}

int freePlace () {
    for (int i = 0; i < 10; ++i) {
        if (strcmp(queue_sensori[i], "") == 0) return i;
    }

    return -1;
}

int busyPlace () {
    for (int i = 0; i < 10; ++i) {
        if (strcmp(queue_sensori[i], "") != 0) return i;
    }

    return -1;
}

void* producer (void* args) {
    while (i < MAX_ELABORATION_DATA) {
        sem_wait(&producer_sem);

        int index = freePlace();

        if (index == -1) {
            printf("Coda piena!\n");

            continue;
        }

        int random_type = rand() % 3;
        strcpy(queue_sensori[index], tipi_di_sensori[random_type]);
        printf("%s in elaborazione!\n", tipi_di_sensori[random_type]);
        ++i;

        sem_post(&consumer_sem);

        usleep(5000);
    }

    return NULL;
}

void* consumer (void* args) {
    while (k < MAX_ELABORATION_DATA) {
        sem_wait(&consumer_sem);

        int index = busyPlace();

        if (index == -1) printf("Coda vuota!\n");
        else {
            printf("Elaborato %s\n", queue_sensori[index]);
            strcpy(queue_sensori[index], "");
            ++k;

            sem_post(&producer_sem);
        }

        usleep(10000);
    }

    return NULL;
}