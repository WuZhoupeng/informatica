#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PAZIENTI 100
#define MAX_ATTESA   20
#define NUM_PAZIENTI 80

typedef struct {
    int  numero;
    char categoria;
    int  saltati;
    int  in_attesa;
} Paziente;

Paziente    coda[MAX_PAZIENTI];
int         prossimo_numero = 1;
int         pazienti_aggiunti = 0;

pthread_mutex_t mutex;
sem_t           sem_pazienti;

void* dispenser  (void* arg);
void* sportello  (void* arg);
int   trova_prossimo ();

int main (void) {
    srand(time(NULL));

    pthread_t th_dispenser;
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;

    for (int i = 0; i < MAX_PAZIENTI; ++i) {
        coda[i].in_attesa = 0;
    }

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Errore nella creazione del mutex!\n");

        return 1;
    }

    if (sem_init(&sem_pazienti, 0, 0) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (pthread_create(&th_dispenser, NULL, dispenser, NULL) != 0) {
        printf("Errore nella creazione del thread dispenser!\n");

        return 1;
    }

    if (pthread_create(&th1, NULL, sportello, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th2, NULL, sportello, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    if (pthread_create(&th3, NULL, sportello, NULL) != 0) {
        printf("Errore nella creazione del thread!\n");

        return 1;
    }

    pthread_join(th_dispenser, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_pazienti);

    return 0;
}

void* dispenser (void* arg) {
    for (int i = 0; i < NUM_PAZIENTI; ++i) {
        usleep((rand() % 100) * 1000);

        pthread_mutex_lock(&mutex);

        int posto = -1;

        for (int j = 0; j < MAX_PAZIENTI; ++j) {
            if (coda[j].in_attesa == 0) {
                posto = j;
                break;
            }
        }

        if (posto == -1) {
            printf("Coda piena! Paziente perso.\n");
            pthread_mutex_unlock(&mutex);
            continue;
        }

        coda[posto].numero    = prossimo_numero++;
        coda[posto].categoria = 'A' + rand() % 6;
        coda[posto].saltati   = 0;
        coda[posto].in_attesa = 1;
        pazienti_aggiunti++;

        printf("[DISPENSER] Paziente %d aggiunto in coda (categoria %c)\n",
               coda[posto].numero, coda[posto].categoria);

        pthread_mutex_unlock(&mutex);

        sem_post(&sem_pazienti);
    }

    return NULL;
}

int trova_prossimo () {
    int indice_migliore = -1;

    for (int i = 0; i < MAX_PAZIENTI; ++i) {
        if (coda[i].in_attesa == 0) {
            continue;
        }

        if (indice_migliore == -1) {
            indice_migliore = i;
            continue;
        }

        Paziente* candidato = &coda[i];
        Paziente* migliore  = &coda[indice_migliore];

        if (candidato->saltati >= MAX_ATTESA && migliore->saltati < MAX_ATTESA) {
            indice_migliore = i;
            continue;
        }

        if (candidato->saltati >= MAX_ATTESA && migliore->saltati >= MAX_ATTESA) {
            if (candidato->numero < migliore->numero) {
                indice_migliore = i;
            }

            continue;
        }

        if (candidato->categoria < migliore->categoria) {
            indice_migliore = i;
            continue;
        }

        if (candidato->categoria == migliore->categoria) {
            if (candidato->numero < migliore->numero) {
                indice_migliore = i;
            }

            continue;
        }
    }

    return indice_migliore;
}

void* sportello (void* arg) {
    int serviti = 0;

    while (1) {
        sem_wait(&sem_pazienti);

        pthread_mutex_lock(&mutex);

        int indice = trova_prossimo();

        if (indice == -1) {
            pthread_mutex_unlock(&mutex);
            continue;
        }

        int  numero    = coda[indice].numero;
        char categoria = coda[indice].categoria;
        int  saltati   = coda[indice].saltati;

        coda[indice].in_attesa = 0;

        for (int i = 0; i < MAX_PAZIENTI; ++i) {
            if (coda[i].in_attesa == 1) {
                coda[i].saltati++;
            }
        }

        serviti++;

        pthread_mutex_unlock(&mutex);

        usleep((rand() % 200) * 1000);

        printf("[SPORTELLO] Paziente %d servito (categoria %c, saltato %d volte)\n",
               numero, categoria, saltati);

        pthread_mutex_lock(&mutex);

        int tutti_serviti = (serviti >= NUM_PAZIENTI / 3) && (pazienti_aggiunti >= NUM_PAZIENTI);

        int ancora_in_attesa = 0;

        for (int i = 0; i < MAX_PAZIENTI; ++i) {
            if (coda[i].in_attesa == 1) {
                ancora_in_attesa++;
            }
        }

        pthread_mutex_unlock(&mutex);

        if (pazienti_aggiunti >= NUM_PAZIENTI && ancora_in_attesa == 0) {
            break;
        }
    }

    return NULL;
}