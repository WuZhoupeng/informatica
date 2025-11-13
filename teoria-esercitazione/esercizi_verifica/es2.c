#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool palindroma (char* p);

int main() {
    char* parola = calloc(100, sizeof(char));

    if (parola == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        exit(1);
    }

    printf("\nInserisci la stringa che vuoi vedere che sia palindroma: ");
    scanf("%99s", parola);

    bool isPalindroma = palindroma(parola);

    if (isPalindroma) printf("\nParola palindroma\n");
    else printf("\nParola non palindroma\n");

    free(parola);
}

bool palindroma (char* p) {
    int size = strlen(p);
    char* reversed = calloc(size, sizeof(char));

    if (reversed == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        *(reversed + i) = *(p + size - i - 1);
    }

    if (strcmp(p, reversed) == 0) return true;
    else return false; 
}