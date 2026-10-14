
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_STAMPANTI 3
#define NUM_STUDENTI 10
#define CICLI_PER_STUDENTE 5

int stampanti_libere = NUM_STAMPANTI;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_stampanti;

void richiediStampa(int id)
{
    printf("[Studente %2d] In attesa di una stampante...\n", id);

    sem_wait(&sem_stampanti);

    pthread_mutex_lock(&mutex);
    stampanti_libere--;
    printf("[Studente %2d] Inizia a stampare. Stampanti libere: %d\n",
           id, stampanti_libere);
    pthread_mutex_unlock(&mutex);
}

void rilasciaStampante(int id)
{
    pthread_mutex_lock(&mutex);
    stampanti_libere++;
    printf("[Studente %2d] Ha finito di stampare. Stampanti libere: %d\n",
           id, stampanti_libere);
    pthread_mutex_unlock(&mutex);

    sem_post(&sem_stampanti);
}

void *studenteThread(void *args)
{
    int id = *(int *)args;
    free(args);

    for (int ciclo = 0; ciclo < CICLI_PER_STUDENTE; ciclo++)
    {
        richiediStampa(id);

        usleep(500000 + rand() % 500000);

        rilasciaStampante(id);

        usleep(100000 + rand() % 200000);
    }

    return NULL;
}

int main(void)
{
    srand(time(NULL));

    if (sem_init(&sem_stampanti, 0, NUM_STAMPANTI) != 0)
    {
        fprintf(stderr, "Errore creazione semaforo\n");
        return 1;
    }

    pthread_t threads[NUM_STUDENTI];

    for (int i = 0; i < NUM_STUDENTI; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        if (pthread_create(&threads[i], NULL, studenteThread, id) != 0)
        {
            fprintf(stderr, "Errore creazione thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < NUM_STUDENTI; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&sem_stampanti);
    pthread_mutex_destroy(&mutex);

    printf("\nTutte le stampe completate.\n");
    return 0;
}