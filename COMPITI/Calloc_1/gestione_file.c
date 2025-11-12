#include "gestione_file.h"

int loadFromFile (struct Studente* studenti, const char filename[], const int nStud) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        return -1;
    }

    char nome[30], cognome[30];
    int anni, num;

    fscanf(file, "%d", &num);
    
    for (int i = nStud; i < nStud+num; ++i) {
        fscanf(file, "%29s", nome);
        fscanf(file, "%29s", cognome);
        fscanf(file, "%d", &anni);

        strcpy((studenti + i)->nome, nome);
        strcpy((studenti + i)->cognome, cognome);
        (studenti + i)->anni = anni;
    }

    fclose(file);
    printf("\n%d studenti caricati dal file", num);
    
    return nStud+num;
}

bool saveToFile (const struct Studente* studenti, const int nStud, const char filename[]) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        return false;
    }

    fprintf(file, "%d\n", nStud);

    for (int i = 0; i < nStud; ++i) {
        fprintf(file, "%s ", (studenti + i)->nome);
        fprintf(file, "%s ", (studenti + i)->cognome);
        fprintf(file, "%d\n", (studenti + i)->anni);
    }

    fclose(file);

    return true;
}

void showStudent (const struct Studente* studenti, const int nStud, const int index) {
    if (!(index < nStud)) {
        fprintf(stderr, "\nImpossibile visualizzare lo studente. Non esiste l'indice %d", index);

        return;
    }

    printf("\nNome: %s ", (studenti + index)->nome);
    printf("Cognome: %s ", (studenti + index)->cognome);
    printf("Anni: %d\n", (studenti + index)->anni);
}

void showAllStudents (const struct Studente* studenti, const int nStud) {
    for (int i = 0; i < nStud; ++i) {
        printf("Nome: %s ", (studenti + i)->nome);
        printf("Cognome: %s ", (studenti + i)->cognome);
        printf("Anni: %d\n", (studenti + i)->anni);
    }
}

int searchByName (const struct Studente* studenti, const int nStud, const char name[]) {
    for (int i = 0; i < nStud; ++i) {
        if (strcmp((studenti + i)->nome, name) == 0) return i;
    }

    return -1;
}

int addStudent (struct Studente* studenti, const struct Studente* stud, int nStud, const int totStud) {
    if (!(nStud < totStud)) return -1;
    
    strcpy((studenti + nStud)->nome, stud->nome);
    strcpy((studenti + nStud)->cognome, stud->cognome);
    (studenti + nStud)->anni = stud->anni;
    
    nStud++;

    return nStud;
}

int deleteStudentsByName (struct Studente* studenti, int nStud, const char name[]) {
    for (int i = 0; i < nStud; ++i) {
        if (strcmp((studenti + i)->nome, name) == 0) {
            strcpy((studenti + i)->nome, (studenti + nStud - 1)->nome);
            strcpy((studenti + i)->cognome, (studenti + nStud - 1)->cognome);
            (studenti + i)->anni = (studenti + nStud - 1)->anni;

            nStud--;

            return nStud;
        }
    }
    
    return -1;
}

int deleteStudent (struct Studente* studenti, int nStud, const int index) {
    if (index < 0 || index >= nStud) {
        return -1;
    }

    strcpy((studenti + index)->nome, (studenti + nStud - 1)->nome);
    strcpy(studenti[index].cognome, (studenti + nStud - 1)->cognome);
    studenti[index].anni = (studenti + nStud - 1)->anni;

    nStud--;

    return nStud;
}