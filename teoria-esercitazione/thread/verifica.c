#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

int stampanti_libere = 3;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_richiedi;
sem_t sem_rilascia;

void* richiediStampa (void* args);
void *rilasciaStampante(void *args);

void test();

int main (void) {
    srand(time(NULL));

    pthread_t th1;
    pthread_t th2;

    if (sem_init(&sem_richiedi, 0, 3) != 0) {
        printf("Errore nella creazione del semaforo!!\n");

        return 1;
    }

    if (sem_init(&sem_rilascia, 0, 0) != 0) {
        printf("Errore nella creazione del semaforo!!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, richiediStampa, NULL) != 0) {
        printf("Errore nella creazione del thread!!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, rilasciaStampante, NULL) != 0) {
        printf("Errore nella creazione del thread!!\n");

        return 1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&sem_richiedi);
    sem_destroy(&sem_rilascia);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *richiediStampa (void *args) {
    for (int i = 0; i < 100; ++i) {
        sem_wait(&sem_richiedi);
        pthread_mutex_lock(&mutex);

        printf("Lo studente %d ha richiesto la stampante\n", i);
        stampanti_libere--;
        printf("[INFO] ci sono ora %d stampanti libere\n", stampanti_libere);
        sem_post(&sem_rilascia);
        usleep(5000 + rand() % 5000);

        pthread_mutex_unlock(&mutex);
    }
}

void *rilasciaStampante (void *args) {
    for (int i = 0; i < 100; ++i) {
        sem_wait(&sem_rilascia);
        pthread_mutex_lock(&mutex);

        printf("Lo studente %d ha stampato con successo\n", i);
        stampanti_libere++;
        printf("[INFO] ci sono ora %d stampanti libere\n", stampanti_libere);
        sem_post(&sem_richiedi);
        usleep(5000 + rand() % 5000);

        pthread_mutex_unlock(&mutex);
    }
}