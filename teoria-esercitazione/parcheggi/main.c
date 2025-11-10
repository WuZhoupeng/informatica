#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Macchina {
    char targa[10];
    int anno;
    char colore[50];
};

struct Parcheggio {
    int id;
    struct Macchina* macchina;
};

int createPostoParcheggio (struct Parcheggio* parcheggio, struct Macchina* macc, size_t n_parcheggi, int* count, int id);

int main() {
    struct Parcheggio* parcheggio = NULL;
    struct Macchina* temp_macchina = malloc(sizeof(struct Macchina));

    if (temp_macchina == NULL) {
        printf("\nErrori nell'allocazione della memoria!");

        exit(1);
    }

    size_t n_parcheggi;
    int scelta, id = 0;

    int* count = malloc(sizeof(int));

    if (count == NULL) {
        printf("\nErrori nell'allocazione della memoria!");
        free(temp_macchina);

        exit(1);
    }

    *count = 0;

    printf("\nInserisci quanti parcheggi ci saranno: ");
    scanf("%zu", &n_parcheggi);

    parcheggio = calloc(n_parcheggi, sizeof(struct Parcheggio));

    if (parcheggio == NULL) {
        printf("\nErrori nell'allocazione della memoria!");
        free(temp_macchina);
        free(count);

        exit(1);
    }

    while (true) {
        printf("\n0. Esci dal programma");
        printf("\n1. Crea un posto di parcheggio per la macchina");
        printf("\n2. Legge le informazioni di una macchina in un posto di parcheggio");
        printf("\n3. Aggiorna le informazioni di una macchina in un posto di parcheggio");
        printf("\n4. Elimina una macchina dal posto di parcheggio");

        printf("\nInserisci una scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 0:
                printf("\nUscita dal programma...");
                return 0;
            case 1:
                printf("\nInserisci la targa della macchina: ");
                scanf("%9s", temp_macchina->targa);
                printf("\nInserisci l'anno di produzione della macchina: ");
                scanf("%d", temp_macchina->anno);
                printf("\nInserisci il colore della macchina: ");
                scanf("%49s", temp_macchina->colore);

                createPostoParcheggio(parcheggio, temp_macchina, n_parcheggi, count, id);

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                printf("\nNon esiste questa scelta, riprova di nuovo...");
                break;
        }
    }
}

int createPostoParcheggio (struct Parcheggio* parcheggio, struct Macchina* macc, size_t n_parcheggi, int* count, int id) {

}