#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_FLOOR 10

int posti[100];
int current_floor = 0;
sem_t sem;

bool isEmpty ();
void* move (void* args);

int main (void) {
    srand(time(NULL));

    if (sem_init(&sem, 0, 1) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    return 0;
}

bool isEmpty () {
    for (int i = 0; i < 100; ++i) {
        if (posti[i] != 0) return false;
    }

    return true;
}

void* move (void* args) {
    sem_wait(&sem);

    while (!isEmpty()) {

    }

    sem_post(&sem);
    return NULL;
}