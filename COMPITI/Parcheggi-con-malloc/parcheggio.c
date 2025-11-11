#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void readPostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research);
void updatePostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research);
void deletePostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research);

int main() {
    struct Parcheggio* parcheggio = NULL;
    struct Macchina* temp_macchina = malloc(sizeof(struct Macchina));

    if (temp_macchina == NULL) {
        printf("\nErrori nell'allocazione della memoria!");

        exit(1);
    }

    size_t n_parcheggi;
    int scelta, id = 0, temp;

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
                for (size_t i = 0; i < *count; ++i) {
                    free((parcheggio + i)->macchina);
                }

                free(temp_macchina);
                free(parcheggio);

                printf("\nUscita dal programma...");
                return 0;
            case 1:
                printf("\nInserisci la targa della macchina: ");
                scanf("%9s", temp_macchina->targa);
                printf("\nInserisci l'anno di produzione della macchina: ");
                scanf("%d", &temp_macchina->anno);
                printf("\nInserisci il colore della macchina: ");
                scanf("%49s", temp_macchina->colore);

                temp = createPostoParcheggio(parcheggio, temp_macchina, n_parcheggi, count, id);

                if (temp == -1) printf("\nNon ci sono più posti");
                else if (temp == -2) {
                    for (size_t i = 0; i < *count; ++i) {
                        free((parcheggio + i)->macchina);
                    }
            
                    free(temp_macchina);
                    free(parcheggio);
            
                    printf("\nErrori nell'allocazione della memoria!");

                    exit(1);
                }
                else {
                    id = temp;
                    printf("\nMacchina parcheggiato con successo");
                }

                break;
            case 2:
                printf("\nInserisci l'id del parcheggio della macchina parcheggiata: ");
                scanf("%d", &temp);

                readPostoParcheggio(parcheggio, count, temp);

                break;
            case 3:
                printf("\nInserisci l'id del parcheggio della macchina parcheggiata che vuoi aggiornare: ");
                scanf("%d", &temp);
                
                updatePostoParcheggio(parcheggio, count, temp);
                
                break;
            case 4:
                printf("\nInserisci l'id del parcheggio della macchina parcheggiata: ");
                scanf("%d", &temp);
                
                deletePostoParcheggio(parcheggio, count, temp);

                break;
            default:
                printf("\nNon esiste questa scelta, riprova di nuovo...");
                break;
        }
    }
}

int createPostoParcheggio (struct Parcheggio* parcheggio, struct Macchina* macc, size_t n_parcheggi, int* count, int id) {
    if (!(*count < n_parcheggi)) return -1;

    (parcheggio + *count)->macchina = malloc(sizeof(struct Macchina));

    if ((parcheggio + *count)->macchina == NULL) {
        return -2;
    }

    // Inserimento dei valori
    (parcheggio + *count)->id = id;
    strcpy((parcheggio + *count)->macchina->targa, macc->targa);
    (parcheggio + *count)->macchina->anno = macc->anno;
    strcpy((parcheggio + *count)->macchina->colore, macc->colore);

    id++;
    (*count)++;

    return id;
}

void readPostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research) {
    for (size_t i = 0; i < *count; ++i) {
        if ((parcheggio + i)->id == id_research) {
            printf("\nID parcheggio: %d", (parcheggio + i)->id);
            printf("\nTarga della macchina: %s", (parcheggio + i)->macchina->targa);
            printf("\nAnno di produzione: %d", (parcheggio + i)->macchina->anno);
            printf("\nColore della macchina: %s", (parcheggio + i)->macchina->colore);

            return;
        }
    }

    printf("\nNon esiste una macchina parcheggiata nell'id indicato (%d)", id_research);
}

void updatePostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research) {
    int temp_index = -1;

    char temp_targa[10];
    int temp_anno;
    char temp_colore[50];

    for (size_t i = 0; i < *count; ++i) {
        if ((parcheggio + i)->id == id_research) {
            temp_index = i;

            break;
        }
    }

    if (temp_index == -1) {
        printf("\nNon esiste una macchina parcheggiata nell'id indicato (%d)", id_research);

        return;
    }

    // Prendo in input i nuovi valori
    printf("\nInserisci la nuova targa della macchina: ");
    scanf("%9s", temp_targa);
    printf("\nInserisci il nuovo anno di produzione della macchina: ");
    scanf("%d", &temp_anno);
    printf("\nInserisci il nuovo colore della macchina: ");
    scanf("%49s", temp_colore);

    // Aggiorno le informazioni
    strcpy((parcheggio + temp_index)->macchina->targa, temp_targa);
    (parcheggio + temp_index)->macchina->anno = temp_anno;
    strcpy((parcheggio + temp_index)->macchina->colore, temp_colore);

    printf("\nInformazioni della macchina nel parcheggio %d aggiornate con successo", id_research);
}

void deletePostoParcheggio (struct Parcheggio* parcheggio, int* count, int id_research) {
    int temp_index = -1;
    
    for (size_t i = 0; i < *count; ++i) {
        if ((parcheggio + i)->id == id_research) {
            temp_index = i;

            break;
        }
    }

    if (temp_index == -1) {
        printf("\nNon esiste una macchina parcheggiata nell'id indicato (%d)", id_research);

        return;
    }

    (parcheggio + temp_index)->id = (parcheggio + *count - 1)->id;
    strcpy((parcheggio + temp_index)->macchina->targa, (parcheggio + *count - 1)->macchina->targa);
    (parcheggio + temp_index)->macchina->anno = (parcheggio + *count - 1)->macchina->anno;
    strcpy((parcheggio + temp_index)->macchina->colore, (parcheggio + *count - 1)->macchina->colore);

    free((parcheggio + *count - 1)->macchina);

    (*count)--;

    printf("\nPosto parcheggio n.%d eliminato con successo", temp_index);
}