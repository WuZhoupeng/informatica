#include <stdio.h>
#include <stdlib.h>

int main() {
    int* memoria = calloc(sizeof(int), 1);
    int size = 1000000;
    size_t count = 1;

    while (memoria != NULL) {
        memoria = malloc(size);
        
        printf("\nCi sono %zu MB\n", count);
        ++count;
    }

    printf("\nCi sono %zu MB\n", count);
    int* p = malloc(sizeof(int));

    if (p == NULL) printf("\nAveva ragione Wu\n");
    else printf("\nAveva ragione Grena\n");
}