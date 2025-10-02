#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void caricaStudente (FILE* file);
void inserisciStudente ();
void stampaStudente ();
void eliminaStudente (int index);
void salvaStudente (FILE* file);

struct Studente {
    char nome[30];
    char cognome[30];
    int anni;
};

struct Studente studente[10];

int main(int argc, char* argv[]) {
    FILE* file_r;
    FILE* file_w;
    int opzione, index;

    while (1) {
        printf("\n1. Carica da un file \n2. Inserisci uno studente \n3. Elenco degli studenti \n4. Elimina uno studente \n5. Salva su un file \n6. Esci");
        printf("\nScegli un'opzione: ");
        scanf("%d", &opzione);

        switch(opzione) {
            case 1:
                caricaStudente(file_r);
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
                salvaStudente(file_w);
                break;
            case 6:
                return 0;
            default:
                printf("\nNon esiste questa opzione");
                break;
        }
    }

    if (file_w == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }
}

void caricaStudente (FILE* file) {
    file = fopen("studenti.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    char nome[30], cognome[30];
    int anni, num;

    fscanf(file, "%d", &num);
    
    for (int i = 0; i < num; ++i) {
        fscanf(file, "%s", &nome);
        fscanf(file, "%s", &cognome);
        fscanf(file, "%d", &anni);
        strcpy(studente[i].nome, nome);
        strcpy(studente[i].cognome, cognome);
        studente[i].anni = anni;
    }

    fclose(file);
}

void inserisciStudente () {
    char nome[30], cognome[30];
    int anni;

    for (int i = 0; i < 10; ++i) {
        printf("\nInserisci nome: ");
        scanf("%29s", &nome);
        strcpy(studente[i].nome, nome);
        printf("\nInserisci cognome: ");
        scanf("%29s", &cognome);
        strcpy(studente[i].cognome, cognome);
        printf("\nInserisci anni: ");
        scanf("%d", &anni);
        studente[i].anni = anni;
    }
}

void stampaStudente () {
    for (int i = 0; i < (sizeof(studente) / sizeof(studente[0])); ++i) {
        printf("Nome: %s ", studente[i].nome);
        printf("Cognome: %s ", studente[i].cognome);
        printf("Anni: %d\n", studente[i].anni);
    }
}

void eliminaStudente (int index) {
    int last_index = sizeof(studente)-1;

    strcpy(studente[index].nome , studente[last_index].nome);
    strcpy(studente[index].cognome, studente[last_index].cognome);
    studente[index].anni = studente[last_index].anni;

    studente[last_index].nome;
    studente[last_index].nome;
    studente[last_index].nome;
}

void salvaStudente (FILE* file) {
    file = fopen("studenti.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");
        exit(1);
    }

    fprintf(file, "%d\n", (sizeof(studente) / sizeof(studente[0])));

    for (int i = 0; i < (sizeof(studente) / sizeof(studente[0])); ++i) {
        fprintf(file, "%s ", studente[i].nome);
        fprintf(file, "%s ", studente[i].cognome);
        fprintf(file, "%d\n", studente[i].anni);
    }

    fclose(file);
}