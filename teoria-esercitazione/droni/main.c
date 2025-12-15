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
bool update_pos (struct Drone* lista_drone, size_t id_drone, char* new_pos);
bool delete (struct Drone** lista_drone, size_t id_drone);

int main() {
    int opzione, temp;
    size_t id_drone, battery_drone;
    char pos_drone[100];

    struct Drone* start = NULL;
    struct Drone* temp_drone = NULL;

    while (true) {
        printf("\nScegli l'opzione: ");
        scanf("%d", &opzione);

        switch (opzione) {
            case 1:
                temp_drone = malloc(sizeof(struct Drone));

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

                break;
            case 2:
                read(start);

                break;
            default:
                printf("\nOpzione non valida!\n");

                break;
        }
    }
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
    if (lista_drone == NULL) return;

    struct Drone* temp = lista_drone;

    while (temp != NULL) {
        printf("ID: %zu Battery: %zu Posizione: %s", (temp)->id, (temp)->battery, (temp)->pos);
        temp = temp->next;
    }
}

bool update_pos(struct Drone* lista_drone, size_t id_drone, char* new_pos) {
    struct Drone* temp = lista_drone;

    while (temp != NULL) {
        if (temp->id == id_drone) {
            strcpy(temp->pos, new_pos);

            return true;
        }

        temp = temp->next;
    }

    return false;
}

bool delete (struct Drone** lista_drone, size_t id_drone) {
    if (*lista_drone == NULL) {

        return false;
    }

    struct Drone* temp = *lista_drone;
    struct Drone* free_d;

    while (temp->next != NULL) {
        if (temp->next != NULL) {
            if (temp->next->id == id_drone) {
                free_d = temp->next;

                if (temp->next->next != NULL) {
                    temp->next = temp->next->next;

                    break;
                }

                temp->next = NULL;

                break;
            }
        }

        temp = temp->next;
    }

    free(free_d);
    return true;
}