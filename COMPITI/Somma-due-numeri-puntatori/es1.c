#include <stdio.h>
#include <stdlib.h>

int* sommaT (int* a, int* b);

int main() {
    int a = 5, b = 10;
    int* somma;

    somma = sommaT(&a, &b);

    if (somma == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        exit(1);
    }

    printf("\nLa somma di %d e di %d è uguale a %d\n", a, b, *somma);

    free(somma);
}

int* sommaT (int* a, int* b) {
    int* result = malloc(sizeof(int));

    if (result == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        return NULL;
    }

    *result = *a + *b;

    return result;
}