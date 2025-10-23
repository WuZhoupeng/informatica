#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Studente {
    char nome[30];
    char cognome[30];
    int anni;
};

int loadFromFile (struct Studente studenti[], const char filename[], const int nStud);

bool saveToFile (const struct Studente studenti[], const int nStud, const char filename[]);

void showStudent (const struct Studente studenti[], const int nStud, const int index);

void showAllStudents (const struct Studente studenti[], const int nStud);

int searchByName (const struct Studente studenti[], const int nStud, const char name[]);

int addStudent (struct Studente studenti[], const struct Studente stud, int nStud, const int totStud);

int deleteStudentsByName (struct Studente studenti[], int nStud, const char name[]);

int deleteStudent (struct Studente studenti[], int nStud, const int index);