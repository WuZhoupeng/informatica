#include "adt.h"
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_TORRI 3

enum CodeError {
    NOT_EXISTENCE_TORRE,
    EMPTY,
    SUCCESSFUL,
    TOO_BIG_VALUE
};

void initialization (stack* head, size_t n_anelli);
void displayTorri (stack* torre);
enum CodeError moveAnello (stack* torre, int partenza, int arrivo);

void my_debug (node* head, node* torre);

int main() {
    int n_anelli;
    int input_part=0, input_arr=0;
    enum CodeError err;

    stack head = NULL;
    stack* torri = calloc(NUMERO_TORRI, sizeof(stack));

    if (torri == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        exit(1);
    }

    while (true) {
        printf("Scegli quanti anelli con cui vuoi giocare: ");
        scanf("%d", &n_anelli);

        if (n_anelli > 1) break;
    }

    initialization(&torri[0], n_anelli);
    printf("\nAnelli inizializzati");

    // *torri = head;

    while (true) {
        displayTorri(torri);

        printf("\nScegli la torre da cui spostare l'anello: ");
        scanf("%d", &input_part);
        
        printf("\nScegli la torre a cui spostare l'anello: ");
        scanf("%d", &input_arr);

        err = moveAnello(torri, input_part, input_arr);
        
        if (err == NOT_EXISTENCE_TORRE) printf("\nNon esiste questa torre");
        if (err == EMPTY) printf("\nQuesta torre è vuota");
        if (err == SUCCESSFUL) printf("\nMossa eseguita correttamente");
        if (err == TOO_BIG_VALUE) printf("\nNon puoi inserire un anello più grande");
    }
}

void initialization (stack* head, size_t n_anelli) {
    for (size_t i = 1; i <= n_anelli; ++i) {
        push(head, i);
    }
}

void displayTorri (stack* torre) {
    for (size_t i = 0; i < NUMERO_TORRI; ++i) {
        print_stack((*(torre + i)));
    }
}

enum CodeError moveAnello (stack* torre, int partenza, int arrivo) {
    if (partenza < 0 || partenza >= NUMERO_TORRI) return NOT_EXISTENCE_TORRE;
    
    if (arrivo < 0 || arrivo >= NUMERO_TORRI) return NOT_EXISTENCE_TORRE;
    if (stack_is_empty((*(torre + partenza)))) return EMPTY;

   
    node* torre_partenza = *(torre + partenza);
    node* torre_arrivo = *(torre + arrivo);
    int valore_anello = pop(&torre_partenza);

    if (stack_is_empty(torre_arrivo)) {
        push(&torre_arrivo, valore_anello);

        return SUCCESSFUL;
    }

    int valore_anello_arrivo = pop(&torre_arrivo);

    if (valore_anello > valore_anello_arrivo) {
        push(&torre_partenza, valore_anello);
        push(&torre_arrivo, valore_anello_arrivo);

        return TOO_BIG_VALUE;
    }

    push(&torre_arrivo, valore_anello_arrivo);
    push(&torre_arrivo, valore_anello);

    return SUCCESSFUL;
}

void my_debug (node* head, node* torre) {
    print_stack(head);
    displayTorri(&torre);
}