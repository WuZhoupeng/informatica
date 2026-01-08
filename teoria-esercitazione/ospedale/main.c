#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct Intervento {
    char* tipo_intervento;
    char* codice_intervento;
    char* descrizione_intervento;
    char* medico_referente;
};

struct Paziente {
    char* name;
    char* surname;
    size_t anno;
    char codice_fiscale[17];
    struct Intervento* intervento;
    struct Paziente* next;
};

void ricoveraPaziente (struct Paziente** coda_paziente, struct Paziente* p);
void visitaPaziente (struct Paziente* coda_paziente, const char* name_paziente);
void dimettiPaziente (struct Paziente** coda_paziente, const char* name_paziente);

int main () {
    bool is_loop = true;
    int opzione;
    char* nome_paziente;
    struct Paziente* inizio_coda = NULL;
    struct Paziente* p = malloc(sizeof(struct Paziente));
    struct Intervento* i = malloc(sizeof(struct Intervento));
    p->intervento = i;

    while (is_loop) {
        printf("\n===== GESTIONE PAZIENTE DELL'OSPEDALE =====\n");
        printf("1. Ricovera un paziente\n");
        printf("2. Visita un paziente\n");
        printf("3. Dimetti un paziente\n");

        printf("Scegli un'opzione: ");
        scanf("%d", &opzione);

        switch (opzione) {
            case 1:
                printf("\nInserisci il nome del paziente: ");
                scanf("%s", p->name);

                printf("\nInserisci il cognome del paziente: ");
                scanf("%s", p->surname);

                printf("\nInserisci l'anno del paziente: ");
                scanf("%zu", &(p->anno));

                printf("\nInserisci il codice fiscale del paziente: ");
                scanf("%s", p->codice_fiscale);

                printf("\nInserisci il tipo di intervento: ");
                scanf("%s", p->intervento->tipo_intervento);

                printf("\nInserisci il codice dell'intervento: ");
                scanf("%s", p->intervento->codice_intervento);

                printf("\nInserisci la descrizione dell'intervento: ");
                scanf("%s", p->intervento->descrizione_intervento);

                printf("\nInserisci il nome del medico referente: ");
                scanf("%s", p->intervento->medico_referente);

                p->next = NULL;

                ricoveraPaziente(&inizio_coda, p);

                printf("Paziente aggiunto alla coda!\n");

                break;
            case 2:
                printf("\nInserisci il nome del paziente che vuoi visitare: ");
                scanf("%s", nome_paziente);

                visitaPaziente(inizio_coda, nome_paziente);

                break;
            case 3:
                printf("\nInserisci il nome del paziente che vuoi dimettere: ");
                scanf("%s", nome_paziente);

                dimettiPaziente(&inizio_coda, nome_paziente);

                printf("Paziente dimesso con successo!\n");

                break;
            case 4:
                is_loop = false;
                break;
            default:
                printf("Opzione non valida\n");
                break;
        }
    }

    while (inizio_coda != NULL) {
        dimettiPaziente(&inizio_coda, inizio_coda->name);
    }

    printf("Tutti i pazienti dimessi!!!\n");
}

void ricoveraPaziente (struct Paziente** coda_paziente, struct Paziente* p) {
    if (*coda_paziente == NULL) {
        *coda_paziente = p;

        return;
    }

    struct Paziente* temp = *coda_paziente;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = p;
}

void visitaPaziente (struct Paziente* coda_paziente, const char* name_paziente) {
    if (coda_paziente == NULL) {
        printf("Non ci sono pazienti in coda!\n");

        return;
    }

    struct Paziente* temp = coda_paziente;

    while (temp != NULL) {
        if (strcmp(temp->name, name_paziente) == 0) {
            printf("Nome paziente: %s\nCognome paziente: %s\nAnno di nascita: %zu\n", temp->name, temp->surname, temp->anno);
            printf("Codice fiscale: %s\nTipo di intervento: %s\n", temp->codice_fiscale, temp->intervento->tipo_intervento);
            printf("Codice intervento: %s\nDescrizione del'intervento: %s\nMedico referente: %s\n", temp->intervento->codice_intervento, temp->intervento->descrizione_intervento, temp->intervento->medico_referente);

            return;
        }

        temp = temp->next;
    }

    printf("Paziente non trovato!\n");
}

void dimettiPaziente (struct Paziente** coda_paziente, const char* name_paziente) {
    if (*coda_paziente == NULL) {
        printf("Non ci sono pazienti in coda!\n");

        return;
    }

    struct Paziente* temp = *coda_paziente;
    struct Paziente* free_p = NULL;

    while (*coda_paziente != NULL) {
        if (strcmp((*coda_paziente)->name, name_paziente) == 0) {
            free_p = (*coda_paziente);

            break;
        }

        *coda_paziente = (*coda_paziente)->next;
    }

    if (free_p == NULL) {
        printf("Paziente non trovato!\n");

        return;
    }
    else {
        if ((*coda_paziente)->next == NULL) {
            *coda_paziente = NULL;
            free(free_p);

            return;
        }
        else {
            *coda_paziente = (*coda_paziente)->next;
            free(free_p);
        }
    }
}