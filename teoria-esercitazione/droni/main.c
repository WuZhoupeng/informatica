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
void read (struct Drone** lista_drone);
bool update_pos(struct Drone** lista_drone, size_t id_drone, char* new_pos);

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

                create(&start, temp_drone);

                break;
            case 2:
                read(&start);

                break;
            default:
                printf("\nOpzione non valida!\n");

                break;
        }
    }
}

void create (struct Drone** lista_drone, struct Drone* d) {
    if (lista_drone == NULL) {
        *lista_drone = d;

        return;
    }
    else {
        struct Drone* temp = *lista_drone;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = d;
    }
}

void read (struct Drone** lista_drone) {
    printf("%p", lista_drone);
    if (lista_drone == NULL) return;

    printf("ID: %zu Battery: %zu Posizione: %s", (*lista_drone)->id, (*lista_drone)->battery, (*lista_drone)->pos);

    read(&(*lista_drone)->next);
}

bool update_pos(struct Drone** lista_drone, size_t id_drone, char* new_pos) {
    if (lista_drone == NULL) {
        return false;
    }

    if ((*lista_drone)->id == id_drone) {

        return true;
    }

    update_pos(&(*lista_drone)->next, id_drone, new_pos);
}