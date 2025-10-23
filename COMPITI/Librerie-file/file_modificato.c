#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "gestione_file.h"

int main() {
    struct Studente studenti[30];
    struct Studente stud;
    const int tot_stud = 30;
    int nStud = 0;
    const char filename[100];
    char name[30];
    int index, opzione, temp;
    bool saved;

    printf("Inserisci il nome del file per caricare e salvare gli studenti: ");
    scanf("%99s", filename);

    while (1) {
        printf("\n1. Carica da un file \n2. Salva su un file \n3. Mostra uno studente \n4. Elenco degli studenti \n5. Cerca da un nome \n6. Inserisci uno studente \n7. Elimina studente per nome \n8. Elimina studente per indice \n9. Esci");
        printf("\nScegli un'opzione: ");
        scanf("%d", &opzione);

        switch(opzione) {
            case 1:
                temp = loadFromFile(studenti, filename, nStud);

                if (temp == -1) fprintf(stderr, "\nImpossibile aprire il file");
                else {
                    nStud = temp;
                    printf("\nCi sono %d studenti", nStud);
                }

                break;
            case 2:
                saved = saveToFile(studenti, nStud, filename);

                if (saved) printf("\nElenco di %d studenti salvato sul file", nStud);
                else fprintf(stderr, "\nImpossibile aprire il file");

                break;
            case 3:
                printf("\nInserisci l'indice dello studente che vuoi vedere: ");
                scanf("%d", &index);

                showStudent(studenti, nStud, index);

                break;
            case 4:
                printf("\n");

                showAllStudents(studenti, nStud);
                
                break;
            case 5:
                printf("\nInserisci il nome dello studente da cercare: ");
                scanf("%29s", name);

                index = searchByName(studenti, nStud, name);

                if (index == -1) printf("\nNon esiste uno studente che si chiama %s", name);
                else printf("\nLo studente che si chiama %s si trova nell'indice %d", name, index);
                
                break;
            case 6:
                printf("\nNome? ");
                scanf("%29s", &stud.nome);
                printf("\nCognome? ");
                scanf("%29s", &stud.cognome);
                printf("\nAnni? ");
                scanf("%d", &stud.anni);

                temp = addStudent(studenti, stud, nStud, tot_stud);

                if (temp == -1) printf("\nSei arrivato al limite dell'array. Non puoi aggiungere studenti");
                else {
                    nStud = temp;
                    printf("\nOra ci sono %d studenti", nStud);
                }

                break;
            case 7:
                printf("\nInserisci il nome dello studente da eliminare: ");
                scanf("%29s", name);
                
                temp = deleteStudentsByName(studenti, nStud, name);

                if (temp == -1) printf("\nNon esiste uno studente che si chiama %s", name);
                else {
                    nStud = temp;
                    printf("\nOra ci sono %d studenti", nStud);
                }
                
                break;
            case 8:
                printf("\nInserisci l'indice dello studente che vuoi eliminare: ");
                scanf("%d", &index);
                
                temp = deleteStudent(studenti, nStud, index);

                if (temp == -1) printf("\nIndice non valido. Inserire un valore tra 0 e %d", nStud - 1);
                else {
                    nStud = temp;
                    printf("\nStudente all'indice %d eliminato con successo. L'array ora ha %d elementi", index, nStud);
                }
                
                break;
            case 9:
                printf("\nUscita in corso...\n");
                
                return 0;
            default:
                printf("\nNon esiste questa opzione");
                break;
        }
    }
}