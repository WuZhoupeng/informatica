#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int* arr = NULL;
    int* temp = NULL;
    int n;
    size_t count = 0;
    
    while (true) {
        printf("\nInserisci un numero: ");
        scanf("%d", &n);

        if (n == 0) {
            printf("\nUscita dal ciclo...");
            break;
        }

        count++;

        temp = calloc(count, sizeof(int));

        if (temp == NULL) {
            printf("\nImpossibile allocare memoria");

            if (count != 1) free(arr);

            exit(1);
        }

        if (count != 1) {
            for (size_t i = 0; i < count; ++i) {
                *(temp + i) = *(arr + i);
            }

            free(arr);
        }
        else {
            *temp = n;
        }

        *(temp + count - 1) = n; // Assegna il valore di n all'ultimo indice dell'array

        arr = calloc(count, sizeof(int));

        if (arr == NULL) {
            printf("\nImpossibile allocare memoria");
            free(temp);
            exit(1);
        }

        for (size_t i = 0; i < count; ++i) {
            *(arr + i) = *(temp + i);
        }

        free(temp);
    }
    
    if (count == 0) {
        printf("\nArray vuoto...\n");

        return 0;
    }
    
    printf("\nL'array reversed\n");

    for (size_t i = count; i > 0; --i) {
        printf("%d\n", *(arr + i - 1));
    }

    free(arr);
}