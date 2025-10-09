#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Studenti {
    char nome[30];
    char cognome[30];
    int anni;
};

int loadFromFile (struct studente[], const char[]);
bool saveToFile (struct studente[], int nStud, const char[]);
void showStudent (struct studente[], int nStud, int index);
void showAllStudents (struct studente[], int nStud);
int searchByName (struct studente[], int nStud, const char[]);
int addStudent (struct studente[], struct stud);
int deleteStudentsByName (struct studente[], int nStud, const char[]);
int deleteStudent (struct studente[], int nStud, int index);

int main() {

    return 0;
}

int loadFromFile (struct studente[], const char[], int nStud) {
    FILE* file = fopen(char, "r");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");

        return -1;
    }

    char nome[30], cognome[30];
    int anni, num;

    fscanf(file, "%d", &num);
    
    for (int i = nStud; i < nStud+num; ++i) {
        fscanf(file, "%s", &nome);
        fscanf(file, "%s", &cognome);
        fscanf(file, "%d", &anni);

        strcpy(studente[i].nome, nome);
        strcpy(studente[i].cognome, cognome);
        studente[i].anni = anni;
    }

    fclose(file);
    printf("%d studenti caricati dal file.\n", num);
    
    return nStud+num;
}

bool saveToFile (struct studente[], int nStud, const char[]) {
    FILE* file = fopen(char, "w");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file\n");

        return false;
    }

    fprintf(file, "%d\n", nStud);

    for (int i = 0; i < nStud; ++i) {
        fprintf(file, "%s ", studente[i].nome);
        fprintf(file, "%s ", studente[i].cognome);
        fprintf(file, "%d ", studente[i].anni);
    }

    fclose(file);
    printf("Elenco di %d studenti salvato su file.\n", nStud);

    return true;
}

void showStudent (struct studente[], int nStud, int index) {
    if (!(index < nStud)) {
        fprintf(stderr, "Impossibile visualizzare lo studente. Non esiste l'indice %d\n", index);

        return;
    }

    printf("Nome: %s ", studente[index].nome);
    printf("Cognome: %s ", studente[index].cognome);
    printf("Anni: %d\n", studente[index].anni);
}

void showAllStudents (struct studente[], int nStud) {
    for (int i = 0; i < nStud; ++i) {
        printf("Nome: %s ", studente[i].nome);
        printf("Cognome: %s ", studente[i].cognome);
        printf("Anni: %d\n", studente[i].anni);
    }
}

int searchByName (struct studente[], int nStud, const char[]) {
    for (int i = 0; i < nStud; ++i) {
        if (strcmp(studente[i].nome, char) == 0) return i;
    }

    return -1;
}

int addStudent (struct studente[], struct stud, int nStud, int totStud) {
    if (!(nStud < totStud)) return -1;

    nStud++;

    strcpy(*studente[nStud].nome, stud.nome);
    strcpy(*studente[nStud].cognome, stud.cognome);
    *studente[nStud].anni = stud.anni;

    return nStud;
}

int deleteStudentsByName (struct studente[], int nStud, const char[]) {

}

int deleteStudent (struct studente[], int nStud, int index) {
    if (index < 0 || index >= nStud) {
        printf("Indice non valido. Inserire un valore tra 0 e %d.\n", nStud - 1);

        return;
    }

    strcpy(studente[index].nome, studente[nStud].nome);
    strcpy(studente[index].cognome, studente[nStud].cognome);
    studente[index].anni = studente[nStud].anni;

    nStud--;

    printf("Studente all'indice %d eliminato con successo.\nL'array ora ha %d elementi\n", index, nStud);

    return nStud;
}