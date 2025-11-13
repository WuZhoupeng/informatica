#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uppercaseVocali (char* s1, char* s2);

int main() {
    int size;

    printf("\nInserisci la dimensione della stringa: ");
    scanf("%d", &size);

    char* parola = calloc(size, sizeof(char));

    if (parola == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        exit(1);
    }

    char* new_parola = calloc(size, sizeof(char));

    if (new_parola == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        free(parola);

        exit(1);
    }

    printf("\nInserisci la stringa che vuoi: ");
    scanf("%s", parola);

    uppercaseVocali(parola, new_parola);

    printf("\nParola vecchia: %s", parola);
    printf("\nParola nuova: %s", new_parola);
    printf("\n");
}

void uppercaseVocali (char* s1, char* s2) {
    for (size_t i = 0; i < strlen(s1); ++i) {
        if (*(s1 + i) == 'a' || *(s1 + i) == 'e' || *(s1 + i) == 'i' || *(s1 + i) == 'o' || *(s1 + i) == 'u') {
            *(s2 + i) = *(s1 + i) - 32;
        }
        else {
            *(s2 + i) = *(s1 + i);
        }
    }
}