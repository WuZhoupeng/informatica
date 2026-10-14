
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_AUTOVEICOLI 20
#define MAX_SUL_PONTE 4
#define MAX_CONSECUTIVI 10

/* ── Tipi ── */
typedef enum
{
    NORD = 0,
    SUD = 1
} Direzione;
typedef enum
{
    AUTO,
    AMBULANZA
} TipoVeicolo;

typedef struct
{
    int id;
    Direzione direzione;
    TipoVeicolo tipo;
} Veicolo;

/* ── Stato del ponte ── */
typedef struct
{
    int auto_sul_ponte;
    Direzione direzione_corrente;
    bool ponte_ha_direzione;
    int consecutivi;
    bool ambulanza_in_attesa;
    bool ambulanza_sul_ponte;
} StatoPonte;

StatoPonte ponte = {
    .auto_sul_ponte = 0,
    .ponte_ha_direzione = false,
    .consecutivi = 0,
    .ambulanza_in_attesa = false,
    .ambulanza_sul_ponte = false};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* ── Funzioni helper ── */
static const char *dir_str(Direzione d) { return d == NORD ? "NORD" : "SUD"; }

static bool posso_entrare(const Veicolo *v)
{
    if (ponte.ambulanza_sul_ponte && v->tipo != AMBULANZA)
        return false;

    if (ponte.ponte_ha_direzione &&
        ponte.direzione_corrente != v->direzione &&
        ponte.auto_sul_ponte > 0)
        return false;

    if (ponte.auto_sul_ponte >= MAX_SUL_PONTE)
        return false;

    if (v->tipo != AMBULANZA &&
        ponte.consecutivi >= MAX_CONSECUTIVI &&
        ponte.ponte_ha_direzione &&
        ponte.direzione_corrente == v->direzione)
        return false;

    return true;
}

void *attraversaPonte(void *args)
{
    Veicolo *v = (Veicolo *)args;

    const char *tipo_str = (v->tipo == AMBULANZA) ? "AMBULANZA" : "Auto    ";

    pthread_mutex_lock(&mutex);

    if (v->tipo == AMBULANZA)
        ponte.ambulanza_in_attesa = true;

    while (!posso_entrare(v))
    {
        printf("[%s %2d | %-4s] In attesa di entrare nel ponte\n",
               tipo_str, v->id, dir_str(v->direzione));
        pthread_cond_wait(&cond, &mutex);
    }

    // Entra nel ponte
    if (v->tipo == AMBULANZA)
    {
        ponte.ambulanza_in_attesa = false;
        ponte.ambulanza_sul_ponte = true;
        ponte.consecutivi = 0;
    }

    if (ponte.ponte_ha_direzione &&
        ponte.direzione_corrente != v->direzione)
    {
        ponte.consecutivi = 0;
    }

    ponte.auto_sul_ponte++;
    ponte.consecutivi++;
    ponte.direzione_corrente = v->direzione;
    ponte.ponte_ha_direzione = true;

    printf("[%s %2d | %-4s] Entra nel ponte  (sul ponte: %d)\n",
           tipo_str, v->id, dir_str(v->direzione), ponte.auto_sul_ponte);

    pthread_mutex_unlock(&mutex);

    usleep(300000 + rand() % 400000);

    pthread_mutex_lock(&mutex);

    ponte.auto_sul_ponte--;

    if (v->tipo == AMBULANZA)
        ponte.ambulanza_sul_ponte = false;

    if (ponte.auto_sul_ponte == 0)
        ponte.ponte_ha_direzione = false;

    printf("[%s %2d | %-4s] Esce dal ponte   (sul ponte: %d)\n",
           tipo_str, v->id, dir_str(v->direzione), ponte.auto_sul_ponte);

    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);

    free(v);
    return NULL;
}

int main(void)
{
    srand(time(NULL));

    pthread_t threads[MAX_AUTOVEICOLI];

    for (int i = 0; i < MAX_AUTOVEICOLI; i++)
    {
        Veicolo *v = malloc(sizeof(Veicolo));
        v->id = i;
        v->direzione = rand() % 2;

        v->tipo = (i % 8 == 0) ? AMBULANZA : AUTO;

        usleep(50000 + rand() % 100000);

        if (pthread_create(&threads[i], NULL, attraversaPonte, v) != 0)
        {
            fprintf(stderr, "Errore creazione thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < MAX_AUTOVEICOLI; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("\nTutti i veicoli hanno attraversato il ponte.\n");
    return 0;
}