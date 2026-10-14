#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

int n_articoli = 1000;
sem_t sem;

void* preleva (void* args);
void* rifornisci (void* args);

int main (void) {
    srand(time(NULL));

    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;
    pthread_t th6;

    if (sem_init(&sem, 0, 1) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, preleva, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, preleva, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, preleva, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th4, NULL, rifornisci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th5, NULL, rifornisci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th6, NULL, rifornisci, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    pthread_join(th5, NULL);
    pthread_join(th6, NULL);

    sem_destroy(&sem);

    return 0;
}

void* preleva (void* args) {
    for (int i = 0; i < 1000; ++i) {
        sem_wait(&sem);

        int value_to_remove = rand() % 20 + 1;

        if (n_articoli - value_to_remove < 0) {
            printf("Il magazzino is empty!!\n");

            sem_post(&sem);

            continue;
        }

        n_articoli -= value_to_remove;
        printf("[INFO] Articoli = %d\n", n_articoli);

        sem_post(&sem);

        usleep(100000);
    }

    return NULL;
}

void* rifornisci (void* args) {
    for (int i = 0; i < 1000; ++i) {
        sem_wait(&sem);

        int value_to_add = rand() % 15 + 1;

        n_articoli += value_to_add;
        printf("[INFO] Articoli = %d\n", n_articoli);

        sem_post(&sem);

        usleep(100000);
    }

    return NULL;
}