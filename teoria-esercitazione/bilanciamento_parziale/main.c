#include <stdio.h>
#include <stdbool.h>

bool balanced (const char* text);

int main () {
    char text[] = "((((((())))))))";

    if (balanced(text)) printf("BILANCIATO!!!\n");
    else printf("NON BILANCIATO!!!\n");

    return 0;
}

bool balanced (const char* text) {
    int counter = 0;

    for (int i = 0; *(text + i) != '\0'; ++i) {
        if (*(text + i) == '(') counter++;
        else if (*(text + i) == ')') counter--;

        if (counter < 0) return false;
    }

    return counter == 0;
}