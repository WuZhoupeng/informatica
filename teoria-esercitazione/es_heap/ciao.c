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

/* #include <stdio.h>
#include <stdlib.h>

int main() {
    // Questo programma tenta di allocare tutta la memoria heap disponibile
    // per stimare la sua dimensione totale. Lo fa allocando ripetutamente
    // blocchi di memoria fino a quando l'allocazione non fallisce.

    // Array di puntatori per tenere traccia di tutti i blocchi allocati.
    // Se non li salvassimo, il sistema potrebbe riutilizzare la stessa memoria.
    void **puntatori = NULL;
    size_t numero_puntatori = 0;

    // Dimensione di ogni singolo blocco che proveremo ad allocare.
    // 1MB (1024*1024 bytes) è un buon compromesso tra velocità e granularità.
    const size_t dimensione_blocco = 1024 * 1024;

    size_t totale_allocato = 0;

    printf("Inizio allocazione della memoria in blocchi da 1 MB...\\n");

    while (1) {
        // Prova ad allocare un nuovo blocco di memoria.
        void *blocco = malloc(dimensione_blocco);

        if (blocco == NULL) {
            // Se malloc restituisce NULL, significa che la memoria è esaurita.
            printf("Allocazione fallita. La memoria heap è piena.\\n");
            break;
        }

        // Per tenere traccia del blocco allocato, lo aggiungiamo al nostro array di puntatori.
        // Prima, riallochiamo l'array dei puntatori per fare spazio a quello nuovo.
        numero_puntatori++;
        void **nuovi_puntatori = realloc(puntatori, numero_puntatori * sizeof(void *));

        if (nuovi_puntatori == NULL) {
            // Se non riusciamo ad allocare memoria nemmeno per il puntatore,
            // siamo veramente a corto di memoria.
            printf("Fallimento nell'allocare memoria per l'array di puntatori.\\n");
            free(blocco); // Liberiamo il blocco appena allocato.
            numero_puntatori--;
            break;
        }

        puntatori = nuovi_puntatori;
        puntatori[numero_puntatori - 1] = blocco;
        totale_allocato += dimensione_blocco;

        // Stampa un aggiornamento ogni 100 MB per non intasare l'output
        if (numero_puntatori % 100 == 0) {
             printf("Totale allocato finora: %zu MB\\n", totale_allocato / (1024*1024));
        }
    }

    printf("\\n----------------------------------------------------------\\n");
    printf("Spazio totale allocato con successo nell'heap: %zu byte\\n", totale_allocato);
    printf("Equivalenti a circa: %.2f MB\\n", (double)totale_allocato / (1024 * 1024));
    printf("----------------------------------------------------------\\n");

    // È buona norma liberare tutta la memoria allocata prima di terminare.
    printf("\\nLiberazione della memoria...\\n");
    for (size_t i = 0; i < numero_puntatori; i++) {
        free(puntatori[i]);
    }
    free(puntatori); // Liberiamo anche l'array dei puntatori.
    printf("Memoria liberata correttamente.\\n");

    return 0;
} */