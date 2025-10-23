#include <stdio.h>
#include <string.h>

int my_str_len (char s[]);
int my_str_cmp (char s1[], char s2[]);
int my_str_cmp_modificato (char s1[], char s2[]);
void stampa_upper (char s[]);
void stampa_lower (char s[]);

int main() {
    char str1[100] = "fgsjkghksgj";
    char str2[100] = "fosahgivjag";
    char str3[100] = "Ciao! Amico";
    
    printf("Stringa prima\n");
    printf("%s\n", str3);

    printf("\nStringa dopo\n");
    printf("Stringa maiuscola: ");
    stampa_upper(str3);
    printf("\nStringa minuscola: ");
    stampa_lower(str3);
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