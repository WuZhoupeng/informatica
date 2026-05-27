#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


#define VEICOLI 20
#define N_BAIE_CARICO 3
#define K_VEICOLI 3
#define LIMITE_CAMBIO_DIREZIONE 3


typedef long long id;

typedef enum {
    STANDARD,
    REFRIGERATO
} Categoria;

typedef enum {
    ENTRATA,
    USCITA
} StatoTunnel, Direzione;

typedef struct Veicolo {
    id veicoloId;
    Categoria categoria;
    Direzione direzione;
    struct Veicolo* next;
} Veicolo;


sem_t full_tunnel;
sem_t full_scarico;
sem_t tunnel_wait;
sem_t tunnel_transit;
sem_t scarico_wait;
sem_t scarico_operation;

pthread_mutex_t tunnel_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_entry = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_exit = PTHREAD_COND_INITIALIZER;

int waiting_entry = 0;
int waiting_exit = 0;
int veicoli_nel_tunnel = 0;

StatoTunnel stato_tunnel = ENTRATA;
id stato_tunnel_index = 0;

Veicolo* head_entry = NULL;
Veicolo* back_entry = NULL;
Veicolo* head_special_entry = NULL;
Veicolo* back_special_entry = NULL;

Veicolo* head_exit = NULL;
Veicolo* back_exit = NULL;
Veicolo* head_special_exit = NULL;
Veicolo* back_special_exit = NULL;

id add_stack_tunnel_index = 0;
id pop_stack_tunnel_index = 0;
Veicolo* stack_tunnel[K_VEICOLI] = {};

id add_stack_scarico_index = 0;
id pop_stack_scarico_index = 0;
Veicolo* stack_scarico[N_BAIE_CARICO] = {};

id numero_veicoli;
id numero_veicoli_usciti = 0;

void workOperation (long ms);

void* cycleActivity (void* args);

Veicolo* createVeicolo (id veicoloId, Categoria categoria);
void addVeicoloQueue (Veicolo** head, Veicolo** back, Veicolo* veicolo);
Veicolo* popVeicoloQueue (Veicolo** head, Veicolo** back);
void addVeicoloTunnel (Veicolo* veicolo);
void popVeicoloTunnel ();
void addVeicoloScarico (Veicolo* veicolo);
void popVeicoloScarico ();


void waitTunnelEntry ();
void waitTunnelExit ();
void onVehiclePassed ();


void barPercent ();

int main (void) {
    srand(time(NULL));

    printf("Inserisci quanti veicoli vuoi immetere: ");
    scanf("%lld", &numero_veicoli);

    pthread_t veicoli[numero_veicoli];

    if (sem_init(&full_tunnel, 0, K_VEICOLI) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&full_scarico, 0, N_BAIE_CARICO) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&tunnel_wait, 0, 1) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&tunnel_transit, 0, K_VEICOLI) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&scarico_wait, 0, 1) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    if (sem_init(&scarico_operation, 0, 1) != 0) {
        printf("Errore nella creazione del semaforo!\n");

        return 1;
    }

    for (long long i = 0; i < numero_veicoli; ++i) {
        Categoria categoria = rand() % 2;
        Veicolo* veicolo = createVeicolo(i, categoria);

        if (pthread_create(&veicoli[i], NULL, cycleActivity, veicolo) != 0) {
            printf("Errore nella creazione del thread!\n");

            return 1;
        }
    }

    for (long long i = 0; i < numero_veicoli; ++i) pthread_join(veicoli[i], NULL);

    sem_destroy(&full_tunnel);
    sem_destroy(&full_scarico);
    sem_destroy(&tunnel_wait);
    sem_destroy(&tunnel_transit);
    sem_destroy(&scarico_wait);
    sem_destroy(&scarico_operation);

    pthread_mutex_destroy(&tunnel_mutex);
    pthread_mutex_destroy(&data_mutex);

    pthread_cond_destroy(&cond_entry);
    pthread_cond_destroy(&cond_exit);

    return 0;
}


void workOperation (long ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void* cycleActivity (void* args) {
    Veicolo* veicolo = (Veicolo*) args;

    // Coda tunnel wait
    sem_wait(&tunnel_wait);
    pthread_mutex_lock(&data_mutex);

    veicolo->categoria == STANDARD ? addVeicoloQueue(&head_entry, &back_entry, veicolo) : addVeicoloQueue(&head_special_entry, &back_special_entry, veicolo);
    printf("[ENTRATA] Veicolo %lld (%s) è in coda!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato");

    pthread_mutex_unlock(&data_mutex);
    sem_post(&tunnel_wait);

    // Transito tunnel - entrata
    waitTunnelEntry();

    sem_wait(&full_tunnel);
    sem_wait(&tunnel_transit);

    pthread_mutex_lock(&data_mutex);

    if (head_special_entry != NULL) veicolo = popVeicoloQueue(&head_special_entry, &back_special_entry);
    else veicolo = popVeicoloQueue(&head_entry, &back_entry);

    addVeicoloTunnel(veicolo);
    printf("\n[INFO] Direzione di percorrenza: ENTRATA\n");
    printf("Veicolo %lld (%s) entra nell'entrata del tunnel!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato");
    printf("[INFO] Veicoli nel tunnel: %lld\n\n", add_stack_tunnel_index - pop_stack_tunnel_index);

    pthread_mutex_unlock(&data_mutex);

    workOperation(300 + rand() % 101);

    pthread_mutex_lock(&data_mutex);

    popVeicoloTunnel();

    pthread_mutex_unlock(&data_mutex);

    onVehiclePassed();

    sem_post(&full_tunnel);
    sem_post(&tunnel_transit);

    // Scarico baie
    sem_wait(&full_scarico);
    sem_wait(&scarico_wait);

    pthread_mutex_lock(&data_mutex);

    addVeicoloScarico(veicolo);
    printf("\nVeicolo %lld (%s) è in attesa dello scarico!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato");
    printf("[INFO] Posti di scarico liberi: %lld\n\n", N_BAIE_CARICO - (add_stack_scarico_index - pop_stack_scarico_index));

    pthread_mutex_unlock(&data_mutex);

    sem_post(&scarico_wait);

    // Lavoro in corso...
    long ms = 100 + rand() % 101;
    workOperation(ms);

    // Scarico finito
    sem_wait(&scarico_operation);

    pthread_mutex_lock(&data_mutex);

    popVeicoloScarico();
    printf("\nVeicolo %lld (%s) ha finito di scaricare in %ld ms!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato", ms);
    printf("[INFO] Posti di scarico liberi: %lld\n\n", N_BAIE_CARICO - (add_stack_scarico_index - pop_stack_scarico_index));

    pthread_mutex_unlock(&data_mutex);

    sem_post(&scarico_operation);
    sem_post(&full_scarico);

    // Coda tunnel wait
    sem_wait(&tunnel_wait);
    pthread_mutex_lock(&data_mutex);

    veicolo->categoria == STANDARD ? addVeicoloQueue(&head_exit, &back_exit, veicolo) : addVeicoloQueue(&head_special_exit, &back_special_exit, veicolo);
    printf("[USCITA] Veicolo %lld (%s) è in coda!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato");

    pthread_mutex_unlock(&data_mutex);
    sem_post(&tunnel_wait);

    // Transito tunnel - uscita
    waitTunnelExit();

    sem_wait(&full_tunnel);
    sem_wait(&tunnel_transit);

    pthread_mutex_lock(&data_mutex);

    if (head_special_exit != NULL) veicolo = popVeicoloQueue(&head_special_exit, &back_special_exit);
    else veicolo = popVeicoloQueue(&head_exit, &back_exit);

    addVeicoloTunnel(veicolo);
    printf("\n[INFO] Direzione di percorrenza: USCITA\n");
    printf("Veicolo %lld (%s) entra nell'uscita del tunnel!\n", veicolo->veicoloId, veicolo->categoria == STANDARD ? "standard" : "refrigerato");
    printf("[INFO] Veicoli nel tunnel: %lld\n\n", add_stack_tunnel_index - pop_stack_tunnel_index);

    numero_veicoli_usciti++;
    barPercent();

    pthread_mutex_unlock(&data_mutex);

    workOperation(300 + rand() % 101);

    pthread_mutex_lock(&data_mutex);

    popVeicoloTunnel();

    pthread_mutex_unlock(&data_mutex);

    onVehiclePassed();
    free(veicolo);

    sem_post(&full_tunnel);
    sem_post(&tunnel_transit);

    return NULL;
}


Veicolo* createVeicolo (id veicoloId, Categoria categoria) {
    Veicolo* veicolo = malloc(sizeof(Veicolo));
    veicolo->veicoloId = veicoloId;
    veicolo->categoria = categoria;
    veicolo->direzione = ENTRATA;
    veicolo->next = NULL;

    return veicolo;
}

void addVeicoloQueue (Veicolo** head, Veicolo** back, Veicolo* veicolo) {
    if (*head == NULL) {
        *head = veicolo;
        *back = veicolo;
    }
    else {
        (*back)->next = veicolo;
        *back = (*back)->next;
    }
}

Veicolo* popVeicoloQueue (Veicolo** head, Veicolo** back) {
    Veicolo* temp = *head;
    *head = temp->next;

    if (*head == NULL) {
        *back = NULL;
    }

    temp->next = NULL;

    return temp;
}

void addVeicoloTunnel (Veicolo* veicolo) {
    stack_tunnel[add_stack_tunnel_index % K_VEICOLI] = veicolo;
    add_stack_tunnel_index++;
}

void popVeicoloTunnel () {
    stack_tunnel[pop_stack_tunnel_index % K_VEICOLI] = NULL;
    pop_stack_tunnel_index++;
}

void addVeicoloScarico (Veicolo* veicolo) {
    stack_scarico[add_stack_scarico_index % N_BAIE_CARICO] = veicolo;
    add_stack_scarico_index++;
}

void popVeicoloScarico () {
    stack_scarico[pop_stack_scarico_index % N_BAIE_CARICO] = NULL;
    pop_stack_scarico_index++;
}


void waitTunnelEntry () {
    pthread_mutex_lock(&tunnel_mutex);

    waiting_entry++;

    while (stato_tunnel != ENTRATA) {
        pthread_cond_wait(&cond_entry, &tunnel_mutex);
    }

    waiting_entry--;
    veicoli_nel_tunnel++;

    pthread_mutex_unlock(&tunnel_mutex);
}

void waitTunnelExit () {
    pthread_mutex_lock(&tunnel_mutex);

    waiting_exit++;

    while (stato_tunnel != USCITA) {
        pthread_cond_wait(&cond_exit, &tunnel_mutex);
    }

    waiting_exit--;
    veicoli_nel_tunnel++;

    pthread_mutex_unlock(&tunnel_mutex);
}

void onVehiclePassed () {
    pthread_mutex_lock(&tunnel_mutex);

    veicoli_nel_tunnel--;
    stato_tunnel_index++;

    if (veicoli_nel_tunnel == 0) {
        if ((stato_tunnel == ENTRATA && waiting_entry == 0 && waiting_exit > 0) ||
            (stato_tunnel == USCITA && waiting_exit == 0 && waiting_entry > 0) ||
            (stato_tunnel_index >= LIMITE_CAMBIO_DIREZIONE &&
            ((stato_tunnel == ENTRATA && waiting_exit > 0) ||
            (stato_tunnel == USCITA && waiting_entry > 0)))
        )
        {
            stato_tunnel = (stato_tunnel == ENTRATA ? USCITA : ENTRATA);
            stato_tunnel_index = 0;

            if (stato_tunnel == ENTRATA) pthread_cond_broadcast(&cond_entry);
            else pthread_cond_broadcast(&cond_exit);
        }
    }

    pthread_mutex_unlock(&tunnel_mutex);
}


void barPercent () {
    double percent = (double)numero_veicoli_usciti / (double)numero_veicoli * 100.0;

    printf("%.2f% \n", percent);
}