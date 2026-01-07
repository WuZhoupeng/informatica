#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Drone {
    size_t id;
    size_t battery;
    char pos[100];
    struct Drone* next;
};

void create (struct Drone** lista_drone, struct Drone* d);
void read (struct Drone* lista_drone);
bool update_pos (struct Drone* lista_drone, size_t id_drone);
bool delete (struct Drone** lista_drone, size_t id_drone);
bool update_bat (struct Drone** lista_drone, size_t id_drone);

int main() {
    int opzione, temp;
    size_t id_drone, battery_drone;
    char pos_drone[100];
    bool is_loop = true;

    struct Drone* start = NULL;
    struct Drone* temp_drone = NULL;

    while (is_loop) {
        printf("\n===== MANAGEMENT DRONES =====\n");
        printf("1. Crea un drone\n");
        printf("2. Leggi tutti i droni\n");
        printf("3. Aggiorna la posizione di un drone\n");
        printf("4. Aggiorna la batteria di un drone\n");
        printf("5. Elimina un drone\n");
        printf("6. Exit\n");

        printf("\nScegli l'opzione: ");
        scanf("%d", &opzione);

        switch (opzione) {
            case 1:
                temp_drone = malloc(sizeof(struct Drone));

                if (temp_drone == NULL) {
                    printf("\nErrore nell'allocazione della memoria\n");

                    return 1;
                }

                printf("\nInserisci l'id del drone: ");
                scanf("%zu", &id_drone);
                printf("\nInserisci la batteria del drone: ");
                scanf("%zu", &battery_drone);
                printf("\nInserisci la posizione del drone: ");
                scanf("%99s", pos_drone);

                temp_drone->id = id_drone;
                temp_drone->battery = battery_drone;
                strcpy(temp_drone->pos, pos_drone);
                temp_drone->next = NULL;

                create(&start, temp_drone);

                printf("Drone creato con successo!\n");

                break;
            case 2:
                read(start);

                break;
            case 3:
                printf("\nInserisci l'id del drone: ");
                scanf("%zu", &id_drone);

                bool trovato = update_pos(start, id_drone);
                
                if (trovato) printf("La posizione del drone %zu è stato aggiornato correttamente!\n", id_drone);
                else printf("Drone %zu non è stato trovato\n", id_drone);

                break;
            case 4:
                printf("\nInserisci l'id del drone: ");
                scanf("%zu", &id_drone);

                bool trovato2 = update_bat(&start, id_drone);
                
                if (trovato2) printf("La batteria del drone %zu è stato aggiornato correttamente! (eliminato se la batteria è 0)\n", id_drone);
                else printf("Drone %zu non è stato trovato\n", id_drone);

                break;
            case 5:
                printf("\nInserisci l'id del drone: ");
                scanf("%zu", &id_drone);

                bool trovato3 = delete(&start, id_drone);

                if (trovato3) printf("Il drone %zu è stato eliminato correttamente!\n", id_drone);
                else printf("Drone %zu non è stato trovato\n", id_drone);

                break;
            case 6:
                is_loop = false;

                break;
            default:
                printf("\nOpzione non valida!\n");

                break;
        }
    }

    while (start != NULL) {
        delete (&start, start->id);
    }

    printf("Droni liberati con successo\n");
    
    return 0;
}

void create (struct Drone** lista_drone, struct Drone* d) {
    if (*lista_drone == NULL) {
        *lista_drone = d;

        return;
    }

    struct Drone* temp = *lista_drone;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = d;
}

void read (struct Drone* lista_drone) {
    if (lista_drone == NULL) {
        printf("Lista dei droni vuota\n");

        return;
    }

    struct Drone* temp = lista_drone;

    while (temp != NULL) {
        printf("ID: %zu Battery: %zu Posizione: %s\n", (temp)->id, (temp)->battery, (temp)->pos);
        temp = temp->next;
    }
}

bool update_pos(struct Drone* lista_drone, size_t id_drone) {
    struct Drone* temp = lista_drone;

    while (temp != NULL) {
        if (temp->id == id_drone) {
            printf("\nInserisci la nuova posizione del drone: ");
            scanf("%99s", temp->pos);

            return true;
        }

        temp = temp->next;
    }

    return false;
}

bool delete (struct Drone** lista_drone, size_t id_drone) {
    struct Drone* temp = *lista_drone;
    struct Drone* free_d = NULL;

    while (temp != NULL && temp->id != id_drone) {
        free_d = temp;
        temp = temp->next;
    }

    if (temp == NULL) return false;

    if (free_d == NULL) *lista_drone = temp->next;
    else free_d->next = temp->next;

    free(temp);

    return true;
}

bool update_bat(struct Drone** lista_drone, size_t id_drone) {
    struct Drone* temp = *lista_drone;

    while (temp != NULL) {
        if (temp->id == id_drone) {
            printf("\nInserisci la nuova batteria del drone: ");
            scanf("%zu", &(temp->battery));

            if (temp->battery == 0) return delete(lista_drone, id_drone);

            return true;
        }

        temp = temp->next;
    }

    return false;
}