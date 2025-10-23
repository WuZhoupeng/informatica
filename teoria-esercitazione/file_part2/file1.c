#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTI 10

void caricaStudente ();
void inserisciStudente ();
void stampaStudente ();
void eliminaStudente (int index);
void eliminaStudenteFlag (int index);
void salvaStudente ();

struct Studente {
    char nome[30];
    char cognome[30];
    int anni;
    int exist = 1;
};

struct Studente studente[MAX_STUDENTI];
int num_studenti = 0;

int main(int argc, char* argv[]) {
    int opzione, index;

    while (1) {
        printf("\n1. Carica da un file \n2. Inserisci uno studente \n3. Elenco degli studenti \n4. Elimina uno studente \n5. Salva su un file \n6. Esci");
        printf("\nScegli un'opzione: ");
        scanf("%d", &opzione);

        switch(opzione) {
            case 1:
                caricaStudente();
                break;
            case 2:
                inserisciStudente();
                break;
            case 3:
                stampaStudente();
                break;
            case 4:
                printf("Inserisci uno studente da eliminare (indice): ");
                scanf("%d", &index);
                eliminaStudente(index);
                break;
            case 5:
                salvaStudente();
                break;
            case 6:
                return 0;
            default:
                printf("\nNon esiste questa opzione");
                break;
        }
    }
}

void caricaStudente () {
    FILE* file = fopen("studenti.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    char nome[30], cognome[30];
    int anni, num;

    fscanf(file, "%d", &num);
    
    for (int i = 0; (i < num) && (num_studenti < MAX_STUDENTI); ++i) {
        fscanf(file, "%s", &nome);
        fscanf(file, "%s", &cognome);
        fscanf(file, "%d", &anni);
        strcpy(studente[i].nome, nome);
        strcpy(studente[i].cognome, cognome);
        studente[i].anni = anni;
        num_studenti++;
    }

    fclose(file);
    printf("%d studenti caricati dal file.\n", num_studenti);
}

void inserisciStudente () {
    if (num_studenti >= MAX_STUDENTI) {
        printf("Array pieno. Impossibile inserire nuovi studenti.\n");
        return;
    }

    char nome[30], cognome[30];
    int anni;

    printf("\nInserisci nome: ");
    scanf("%29s", &nome);
    strcpy(studente[num_studenti].nome, nome);
    printf("\nInserisci cognome: ");
    scanf("%29s", &cognome);
    strcpy(studente[num_studenti].cognome, cognome);
    printf("\nInserisci anni: ");
    scanf("%d", &anni);
    studente[num_studenti].anni = anni;

    num_studenti++;
    printf("Studente inserito con successo.\n");
}

void stampaStudente () {
    for (int i = 0; i < num_studenti; ++i) {
        if (studente[i].exist == 1) {
            printf("Nome: %s ", studente[i].nome);
            printf("Cognome: %s ", studente[i].cognome);
            printf("Anni: %d\n", studente[i].anni);
        }
    }
}

void eliminaStudente (int index) {
    if (index < 0 || index >= num_studenti) {
        printf("Indice non valido. Inserire un valore tra 0 e %d.\n", num_studenti - 1);
        return;
    }

    for (int i = index; i < num_studenti - 1; i++) {
        studente[i] = studente[i + 1];
    }

    num_studenti--;

    printf("Studente all'indice %d eliminato con successo.\nL'array ora ha %d elementi\n", index, num_studenti);
}

void eliminaStudenteFlag (int index) {
    if (index < 0 || index >= num_studenti) {
        printf("Indice non valido. Inserire un valore tra 0 e %d.\n", num_studenti - 1);
        return;
    }

    studente[index].exist = 0;
}

void salvaStudente () {
    FILE* file = fopen("studenti.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    fprintf(file, "%d\n", num_studenti);

    for (int i = 0; i < num_studenti; ++i) {
        fprintf(file, "%s ", studente[i].nome);
        fprintf(file, "%s ", studente[i].cognome);
        fprintf(file, "%d\n", studente[i].anni);
    }

    fclose(file);
    printf("Elenco di %d studenti salvato su file.\n", num_studenti);
}