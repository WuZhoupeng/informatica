#include <stdio.h>
#include <string.h>

int my_str_len (char s[]);
int my_str_cmp (char s1[], char s2[]);
int my_str_cmp_modificato (char s1[], char s2[]);
void stampa_upper (char s[]);
void stampa_lower (char s[]);
void stampa_both (char s[]);

int main() {
    char str1[100] = "fgsjkghksgj";
    char str2[100] = "fosahgivjag";
    char str3[100] = "Ciao! Amico";
    
    /* if (my_str_cmp(str1, str2) == 0) printf("Stringa uguale\n");
    else if (my_str_cmp(str1, str2) == 2) printf("Stringhe diverse: viene prima %s\n", str1);
    else printf("Stringhe diverse: viene prima %s\n", str2); */

    /* if (my_str_cmp_modificato(str1, str2) == -1) printf("Stringa uguale\n");
    else printf("Stringa diversa: si differiscono nella posizione %d\n", my_str_cmp_modificato(str1, str2)); */

    printf("Stringa prima\n");
    printf("%s\n", str3);

    printf("\nStringa dopo\n");
    printf("Stringa maiuscola: ");
    stampa_upper(str3);
    printf("\nStringa minuscola: ");
    stampa_lower(str3);
    printf("\nStringa: ");
    stampa_both(str3);
    printf("\n");
}

int my_str_len (char s[]) {
    int lunghezza = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        lunghezza++;
    }
    
    return lunghezza;
}

int my_str_cmp (char s1[], char s2[]) {
    if (my_str_len(s1) != my_str_len(s2)) return -1;
    
    for (int i = 0; s1[i] != '\0'; ++i) {
        if (s1[i] != s2[i]) {
            if (s1[i] < s2[i]) return 2;
            else return 3;
        }
    }
    
    return 0;
}

int my_str_cmp_modificato (char s1[], char s2[]) {
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; ++i) {
        if (s1[i] != s2[i]) return i;
    }
    
    return -1;
}

void stampa_upper (char s[]) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') printf("%c", s[i] - ' ');
        else printf("%c", s[i]);
    }
}

void stampa_lower (char s[]) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') printf("%c", s[i] + ' ');
        else printf("%c", s[i]);
    }
}

void stampa_both (char s[]) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') printf("%c", s[i] - ' ');
        else if (s[i] >= 'A' && s[i] <= 'Z') printf("%c", s[i] + ' ');
        else printf("%c", s[i]);
    }
}




/* int main() {
    char stringa[10] = "Ciao";
    
    printf("%s\n", stringa);
    
    for (int i = 0; i < 10; ++i) {
        printf("%c [%d]\n", stringa[i], stringa[i]);
        }
        
        // Indirizzo
        printf("0x%x\n", stringa);
        
        strcat(stringa, " Wu");
        printf("%s\n", stringa);
        
    // Copiare da stringa a stringa
    char stringa2[10];
    strcpy(stringa2, stringa);
    printf("%s 0x%x\n", stringa2, stringa2);

    // Comparazione tra due stringhe
    if (strcmp(stringa, stringa2) == 0) printf("Stringhe uguali\n");
    else printf("Stringhe diverse\n");
} */