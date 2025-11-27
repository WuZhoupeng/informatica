#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Note {
    char descrizione[100];
    struct Note* next;
};

struct Artefatto {
    int codice_arcano;
    char nome[30];
    float mana;
    struct Note* nota;
    struct Artefatto* next;
};

void printNote (struct Note* lista_nota);
void freeArtefatto (struct Artefatto* lista_artefatti);
void freeNote (struct Note* lista_nota);
void freeNoteAll (struct Artefatto* lista_artefatti);
void addArtefatto (struct Artefatto** lista_artefatti, struct Artefatto* artefatto);
void consultArtefatti (struct Artefatto* lista_artefatti);
void modifyArtefatto (struct Artefatto* lista_artefatti, int codice_arcano);
void addNote (struct Note** lista_nota, struct Note* nota, struct Artefatto* lista_artefatti, int codice_arcano);
void printNoteArtefatto (struct Note* lista_nota, struct Artefatto* lista_artefatti, int codice_arcano);
void removeArtefatto (struct Artefatto** lista_artefatti, struct Note** lista_nota, int codice_arcano);

int main() {
    int opzione;
    bool is_running = true;

    int codice_arcano;
    char nome[30];
    float mana;
    struct Note* nota;

    struct Artefatto* head = NULL;
    struct Artefatto* artefatto = NULL;

    while (is_running) {
        printf("\n0. Exit");
        printf("\n1. Aggiungi un nuovo artefatto alla collezione");
        printf("\n2. Consulta l'elenco completo degli artifatti nell'archivio");
        printf("\n3. Modifica informazioni di un artefatto");
        printf("\n4. Leggi tutte le note di un artefatto");
        printf("\n5. Aggiungi una nuova nota in un artefatto");
        printf("\n6. Rimuovi un artefatto");
        
        printf("\nScegli l'opzione: ");
        scanf("%d", &opzione);

        switch (opzione) {
            case 0:
                is_running = false;

                break;
            case 1:
                artefatto = malloc(sizeof(struct Artefatto));

                if (artefatto == NULL) {
                    printf("\nErrore nell'allocazione della memoria");
                    is_running = false;

                    break;
                }
                
                nota = malloc(sizeof(struct Note));
                
                if (nota == NULL) {
                    printf("\nErrore nell'allocazione della memoria");
                    is_running = false;

                    break;
                }

                printf("\nCodice arcano: ");
                scanf("%d", &codice_arcano);

                printf("\nNome: ");
                scanf("%29s", nome);

                printf("\nMana: ");
                scanf("%f", &mana);

                printf("\nNota: ");
                scanf("%99s", nota->descrizione);

                artefatto->codice_arcano = codice_arcano;
                strcpy(artefatto->nome, nome);
                artefatto->mana = mana;
                artefatto->next = NULL;
                artefatto->nota = nota;
                artefatto->nota->next = NULL;

                addArtefatto(&head, artefatto);

                printf("\nAggiunto correttamente");

                artefatto = NULL;
                nota = NULL;

                break;
            case 2:
                consultArtefatti(head);

                break;
            case 3:
                printf("\nInserisci il codice arcano del artefatto che vuoi modificare: ");
                scanf("%d", &codice_arcano);

                modifyArtefatto(head, codice_arcano);

                break;
            case 4:
                printf("\nInserisci il codice arcano del artefatto che vuoi modificare: ");
                scanf("%d", &codice_arcano);

                printNoteArtefatto(head->nota, head, codice_arcano);

                break;
            case 5:
                nota = malloc(sizeof(struct Note));

                if (nota == NULL) {
                    printf("\nErrore nell'allocazione della memoria");
                    is_running = false;

                    break;
                }
                
                printf("\nInserisci il codice arcano del artefatto che vuoi aggiungere: ");
                scanf("%d", &codice_arcano);

                printf("\nInserire descrizione nota: ");
                scanf("%99s", nota->descrizione);
                
                addNote(&(head->nota), nota, head, codice_arcano);

                break;
            case 6:
                printf("\nInserisci il codice arcano del artefatto che vuoi rimuovere: ");
                scanf("%d", &codice_arcano);
                
                removeArtefatto(&head, &(head->nota), codice_arcano);

                break;
            default:
                printf("\nOpzione non valida");

                break;
        }
    }

    if (head != NULL) {
        freeNoteAll(head);
        freeArtefatto(head);
        printf("\nUscita in corso...\n");
    }

    printf("\nUscita in corso...\n");
}

void printNote (struct Note* lista_nota) {
    struct Note* temp = lista_nota;

    while (temp != NULL) {
        printf("%s", temp->descrizione);

        temp = temp->next;
    }
}

void freeArtefatto (struct Artefatto* lista_artefatti) {
    struct Artefatto* temp;

    while (lista_artefatti != NULL) {
        temp = lista_artefatti;
        lista_artefatti = lista_artefatti->next;

        free(temp);
    }
}

void freeNote (struct Note* lista_nota) {
    struct Note* temp;

    while (lista_nota != NULL) {
        temp = lista_nota;
        lista_nota = lista_nota->next;

        free(temp);
    }
}

void freeNoteAll (struct Artefatto* lista_artefatti) {
    while (lista_artefatti != NULL) {
        freeNote(lista_artefatti->nota);

        lista_artefatti = lista_artefatti->next;
    }
}

void addArtefatto (struct Artefatto** lista_artefatti, struct Artefatto* artefatto) {
    if (*lista_artefatti == NULL) {
        *lista_artefatti = artefatto;

        return;
    }

    struct Artefatto* temp = *lista_artefatti;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = artefatto;
}

void consultArtefatti (struct Artefatto* lista_artefatti) {
    if (lista_artefatti == NULL) {
        printf("\nArchivio vuoto");

        return;
    }

    struct Artefatto* temp = lista_artefatti;

    while (temp != NULL) {
        printf("\nCodice arcano: %d \nNome: %s \nValore mana: %f \nNote: ", temp->codice_arcano, temp->nome, temp->mana);
        printNote(temp->nota);
        printf("\n");

        temp = temp->next;
    }
}

void modifyArtefatto (struct Artefatto* lista_artefatti, int codice_arcano) {
    char nome_temp[30];
    float mana_temp;

    if (lista_artefatti == NULL) {
        printf("\nArchivio vuoto");

        return;
    }

    struct Artefatto* temp = lista_artefatti;

    while (temp != NULL) {
        if (temp->codice_arcano == codice_arcano) {
            printf("\nNuovo nome? ");
            scanf("%29s", nome_temp);

            printf("\nNuovo valore mana? ");
            scanf("%f", &mana_temp);

            strcpy(temp->nome, nome_temp);
            temp->mana = mana_temp;

            printf("\nArtefatto %d modificato con successo!", codice_arcano);

            return;
        }

        temp = temp->next;
    }

    printf("\nArtefatto non trovato");
}

void addNote (struct Note** lista_nota, struct Note* nota, struct Artefatto* lista_artefatti, int codice_arcano) {
    if (lista_artefatti == NULL) {
        printf("\nArchivio vuoto");

        return;
    }

    struct Artefatto* temp_artefatto = lista_artefatti;

    while (temp_artefatto != NULL) {
        if (temp_artefatto->codice_arcano == codice_arcano) {
            if (*lista_nota == NULL) {
                *lista_nota = nota;
        
                return;
            }
        
            struct Note* temp_nota = *lista_nota;
        
            while (temp_nota->next != NULL) {
                temp_nota = temp_nota->next;
            }
        
            temp_nota->next = nota;

            return;
        }

        temp_artefatto = temp_artefatto->next;
    }
}

void printNoteArtefatto (struct Note* lista_nota, struct Artefatto* lista_artefatti, int codice_arcano) {
    if (lista_artefatti == NULL) {
        printf("\nArchivio vuoto");

        return;
    }

    struct Artefatto* temp_artefatto = lista_artefatti;

    while (temp_artefatto != NULL) {
        if (temp_artefatto->codice_arcano == codice_arcano) {
            struct Note* temp_nota = lista_nota;

            while (temp_nota != NULL) {
                printf("\n%s", temp_nota->descrizione);

                temp_nota = temp_nota->next;
            }

            return;
        }

        temp_artefatto = temp_artefatto->next;
    }
}

void removeArtefatto (struct Artefatto** lista_artefatti, struct Note** lista_nota, int codice_arcano) {
    if (lista_artefatti == NULL) {
        printf("\nArchivio vuoto");

        return;
    }

    struct Artefatto* temp_artefatto = *lista_artefatti;
    struct Artefatto* prev_artefatto;

    while (temp_artefatto->next != NULL) {
        if (temp_artefatto->next->codice_arcano == codice_arcano) prev_artefatto = temp_artefatto;

        if (temp_artefatto->codice_arcano == codice_arcano) {
            prev_artefatto->next = temp_artefatto->next;

            freeNote(temp_artefatto->nota);
            free(temp_artefatto);

            return;
        }

        temp_artefatto = temp_artefatto->next;
    }
}