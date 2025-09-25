#include <stdio.h>

void inserisciNumero(int dimensione[]);
void creaCornice(int lun, int lar);

int main (int argc, char *argv[]) {
    /*
        int main (int argc, char *argv[]) {
            int n;
            if (argc > 1) n = atoi(argv[1]);
        }
    */

    int dimensione[2];

    if (argc == 3) {
        int a, b;
        a = atoi(argv[1]);
        b = atoi(argv[2]);

        creaCornice(a, b);
    } else {
        inserisciNumero(dimensione);
        creaCornice(dimensione[0], dimensione[1]);
    }
}

void inserisciNumero(int dimensione[]) {
    int lunghezza, larghezza;
    printf("Inserisci la lunghezza: ");
    scanf("%d", &lunghezza);
    dimensione[0] = lunghezza;
    printf("\nInserisci la larghezza: ");
    scanf("%d", &larghezza);
    dimensione[1] = larghezza;
}

void creaCornice(int lun, int lar) {
    for (int i = 0; i < lun; ++i) {
        for (int k = 0; k < lar; ++k) {
            if (i == 0 || i == lar-1 || k == 0 || k == lar-1) printf("X");
            else printf(" ");
        }

        printf("\n");
    }
}