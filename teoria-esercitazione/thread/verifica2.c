#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_AUTOVEICOLI 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t semaforo;
sem_t attraversamento;
int i = 0, k = 0;

typedef enum Senso {
    NORD,
    SUD
} Direzione;

typedef struct Autoveicolo {
    int id;
    Direzione direzione;
    bool precedenza_assoluta;
    bool checked;
} Automobile;

Automobile automobili[MAX_AUTOVEICOLI];

void* attraversaPonte (void* args);
void* attraversato (void* args);

int main (void) {
    srand(time(NULL));

    for (int i = 0; i < MAX_AUTOVEICOLI; ++i) {
        automobili[i].id = i;
        automobili[i].direzione = rand() % 2;

        if (i % 10 == 0) automobili[i].precedenza_assoluta = true;
        else automobili[i].precedenza_assoluta = false;

        automobili[i].checked = false;
    }

    pthread_t th1;
    pthread_t th2;

    if (sem_init(&semaforo, 0, 4) != 0) {
        printf("Errore nella creazione del semaforo!!\n");

        return 1;
    }

    if (sem_init(&attraversamento, 0, 0) != 0) {
        printf("Errore nella creazione del semaforo!!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, attraversaPonte, NULL) != 0) {
        printf("Errore nella creazione del thread!!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, attraversato, NULL) != 0) {
        printf("Errore nella creazione del thread!!\n");

        return 1;
    }

    sem_post(&attraversamento);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&semaforo);
    sem_destroy(&attraversamento);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *attraversaPonte(void *args) {
    while (i < MAX_AUTOVEICOLI - 1) {
        sem_wait(&semaforo);

        pthread_mutex_lock(&mutex);
        if (automobili[i+1].checked) {
            printf("Veicolo %d attraversa\n", automobili[i + 1].id);
            sem_post(&attraversamento);
            ++i;
            pthread_mutex_unlock(&mutex);

            continue;
        }

        if (automobili[i].direzione == automobili[i+1].direzione) {
            printf("Veicolo %d attraversa\n", automobili[i+1].id);
            sem_post(&attraversamento);
            ++i;
            pthread_mutex_unlock(&mutex);
        }
        else {
            printf("Veicolo %d non attraversa: direzione opposta\n", automobili[i+1].id);
            automobili[i].checked = true;
            ++i;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

void* attraversato (void* args) {
    while (k < MAX_AUTOVEICOLI) {
        sem_wait(&attraversamento);

        printf("Veicolo %d ha appena attraversato il ponte\n", automobili[k].id);
        ++k;

        sem_post(&semaforo);
    }

    return NULL;
}