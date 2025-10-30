#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int* arr;
    int* temp;
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

        temp = malloc(count * sizeof(int));

        if (temp == NULL) {
            printf("\nImpossibile allocare memoria");
            exit(1);
        }

        if (count != 1) {
            for (size_t i = 0; i < count - 1; ++i) {
                *(temp + i) = *(arr + i);
            }

            free(arr);
        }
        else {
            *temp = n;
        }

        *(temp + count - 1) = n;
        arr = malloc(count * sizeof(int));

        if (arr == NULL) {
            printf("\nImpossibile allocare memoria");
            exit(1);
        }

        for (size_t i = 0; i < count; ++i) {
            *(arr + i) = *(temp + i);
        }

        free(temp);
    }
    
    printf("\nL'array reversed\n");

    for (size_t i = count - 1; i > 0; --i) {
        printf("%d\n", *(arr + i));
    }
}