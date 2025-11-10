#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Macchina {
    char targa[10];
    int anno;
    char colore[50];
};

struct Parcheggio {
    int id;
    struct Macchina* macchina;
};



int main() {
    struct Parcheggio* parcheggio;
    int n_parcheggi, scelta;

    printf("\nInserisci quanti parcheggi ci saranno: ");
    scanf("%d", &n_parcheggi);

    parcheggio = calloc(n_parcheggi, sizeof(struct Parcheggio));

    while (true) {
        printf("\nInserisci una scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }
}