#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    /*
        Scrivere in file
    */
    FILE* file = fopen("a.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    fprintf(file, "Ciao universo\n");
    fclose(file);

    /*
        Leggere in file
    */
    file = fopen("a.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    char stringa[20];
    fscanf(file, "%19s", stringa);
    printf("%s\n", stringa);
    fscanf(file, "%19s", stringa);
    printf("%s\n", stringa);
    fclose(file);
}