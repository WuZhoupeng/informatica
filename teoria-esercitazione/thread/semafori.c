#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

unsigned int CNT = 0;
unsigned int c_step = 0;
unsigned int c_action = 0;
int finish = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void* step ();
void* action ();

int main (void) {
    srand(time(NULL));

    pthread_t th1;
    pthread_t th2;

    if (sem_init(&sem, 0, 0) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, step, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, action, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }


    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("Cicli step: %u\n", c_step);
    printf("Cicli action: %u\n", c_action);

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* step () {
    for (;;) {
        pthread_mutex_lock(&mutex);

        if (CNT >= 100000) {
            finish = 1;
            pthread_mutex_unlock(&mutex);
            sem_post(&sem);

            break;
        }

        ++CNT;
        c_step++;

        if (CNT % 10 == 0) {
            sem_post(&sem);
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* action () {
    for (;;) {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);

        if (finish || CNT >= 100000) {
            pthread_mutex_unlock(&mutex);

            break;
        }

        CNT += (unsigned int) rand() % 6;
        c_action++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}