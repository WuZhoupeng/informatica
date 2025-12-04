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

void initialization (node** head, size_t n_anelli);
void displayTorri (node* torre);
enum CodeError moveAnello (node** torre, size_t partenza, size_t arrivo);

void my_debug (node* head, node* torre);

int main() {
    int n_anelli;

    node* head = NULL;
    node* torri = calloc(NUMERO_TORRI, sizeof(node));

    if (torri == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        exit(1);
    }

    while (true) {
        printf("Scegli quanti anelli con cui vuoi giocare: ");
        scanf("%d", &n_anelli);

        if (n_anelli > 1) break;
    }

    initialization(&head, n_anelli);
    printf("\nAnelli inizializzati");

    *torri = *head;
    
    displayTorri(torri);
}

void initialization (node** head, size_t n_anelli) {
    for (size_t i = 1; i <= n_anelli; ++i) {
        push(head, i);
    }
}

void displayTorri (node* torre) {
    for (size_t i = 0; i < NUMERO_TORRI; ++i) {
        print_stack(&(*(torre + i)));
    }
}

enum CodeError moveAnello (node** torre, size_t partenza, size_t arrivo) {
    if (partenza < 0 || partenza > NUMERO_TORRI) {
        printf("\nNon esiste questa torre");

        return NOT_EXISTENCE_TORRE;
    }
    
    if (arrivo < 0 || arrivo > NUMERO_TORRI) {
        printf("\nNon esiste questa torre");

        return NOT_EXISTENCE_TORRE;
    }

    if (stack_is_empty((*torre + partenza))) {
        printf("\nQuesta torre è vuota");

        return EMPTY;
    }

    node* torre_partenza = (*torre + partenza);
    node* torre_arrivo = (*torre + arrivo);
    int valore_anello = pop(&torre_partenza);

    if (stack_is_empty(torre_arrivo)) {
        push(&torre_arrivo, valore_anello);

        printf("\nMossa eseguita correttamente");
        return SUCCESSFUL;
    }

    int valore_anello_arrivo = pop(&torre_arrivo);

    if (valore_anello > valore_anello_arrivo) {
        printf("\nNon puoi inserire un anello più grande");

        return TOO_BIG_VALUE;
    }

    push(&torre_arrivo, valore_anello_arrivo);
    push(&torre_arrivo, valore_anello);

    printf("\nMossa eseguita correttamente");
    return SUCCESSFUL;
}

void my_debug (node* head, node* torre) {
    print_stack(head);
    displayTorri(torre);
}