#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isSubstr (char* a, char* b);

int main() {
    char* parola1 = calloc(100, sizeof(char));
    
    if (parola1 == NULL) {
        printf("\nErrori nell'allocazione della memoria");
        
        exit(1);
    }
    
    
    char* parola2 = calloc(100, sizeof(char));

    if (parola2 == NULL) {
        printf("\nErrori nell'allocazione della memoria");

        free(parola1);

        exit(1);
    }

    printf("\nParola1: ");
    scanf("%99s", parola1);

    printf("\nParola2: ");
    scanf("%99s", parola2);

    bool dentro = isSubstr(parola1, parola2);

    if (dentro) printf("\nDentro");
    else printf("\nFuori");

    printf("\n");

    free(parola1);
    free(parola2);
}

bool isSubstr (char* a, char* b) {
    int count = 0;

    for (size_t i = 0; i < strlen(a); ++i) {
        
        for (size_t k = 0; k < strlen(b); ++k) {
            if (*(a + i + k) == *(b + k)) {
                count++;
            }
        }

        if (count == strlen(b)) break;
        
        count = 0;
    }

    if (count == strlen(b)) return true;
    else return false;
}