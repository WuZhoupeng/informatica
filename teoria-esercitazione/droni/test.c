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

int main() {
    int opzione;
    struct Drone** start = NULL;

    struct Drone* d = malloc(sizeof(struct Drone));

    if (d == NULL) {
        printf("Errore");
        exit(1);
    }
    d->id = 100;
    d->battery = 45;
    strcpy(d->pos, "Europa");
    d->next = NULL;

    printf("\nTest");
    start = &d;

    printf("\n%zu %zu %s %p\n", (*start)->id, (*start)->battery, (*start)->pos, (*start)->next);
}