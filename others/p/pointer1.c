#include <stdio.h>

void cambia (int* a);
void stampa (int* a);
void stampaArr (int arr[], int dimensione);
void arrDispari (int arr[], int dimensione);

int main() {
    int a = 1901;
    int arr[] = {5, 4, 6, 8, 1, 9};

    stampa(&a);
    cambia(&a);
    stampa(&a);

    stampaArr(arr, 6);
    arrDispari(arr, 6);
    stampaArr(arr, 6);

    return 0;
}

void cambia (int* a) {
    for (int i = 0; i < 10; i++){
        if (i % 2 == 0) {
            *a += i;
        }
    }
}

void stampa (int* a) {
    printf("Il valore è %d e l'indirizzo è %p\n", *a, a);
}

void stampaArr (int arr[], int dimensione) {
    for (int i = 0; i < dimensione; ++i) {
        printf("%d ", *(arr + i));
    }

    printf("\n");
}

void arrDispari (int arr[], int dimensione) {
    for (int i = 0; i < dimensione; ++i) {
        if (*(arr + i) % 2 == 0) *(arr + i) += 3;
    }
}