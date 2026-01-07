#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool balanced (const char* text);

int main () {
    char text[] = "((((((((((([[[[]]]]]]]]]]þ[þ[þ[][]]][{}{}}{}])))))";
    
    if (balanced(text)) printf("BILANCIATO!!!\n");
    else printf("NON BILANCIATO!!!\n");
    
    return 0;
}

bool balanced (const char* text) {
    int size = strlen(text);
    char stack[size];
    int top = -1;

    for (int i = 0; i < size; ++i) {
        char current_char = *(text + i);

        if (current_char == '(' || current_char == '[' || current_char == '{') {
            stack[++top] = current_char;
        }
        else if (current_char == ')' || current_char == ']' || current_char == '}') {
            if (top == -1) {
                return false;
            }

            char top_char = stack[top--];

            if ((current_char == ')' && top_char != '(') ||
                (current_char == ']' && top_char != '[') ||
                (current_char == '}' && top_char != '{')) {
                return false;
            }
        }
    }

    return top == -1;
}
































/* struct Counter {
    int tonde;
    int quadre;
    int graffe;
}; */

/* struct Counter c = {0, 0, 0};
char last_text;

for (int i = 0; *(text + i) != '\0'; ++i) {
    if (*(text + i) == '(') {
        c.tonde++;
        last_text = *(text + i);
    }
    else if (*(text + i) == '[') {
        c.quadre++;
        last_text = *(text + i);
    }
    else if (*(text + i) == '{') {
        c.graffe++;
        last_text = *(text + i);
    }
    else if (*(text + i) == ')') {
        c.tonde--;
        
        if (last_text == '[' || last_text == '{') return false;
    }
    else if (*(text + i) == ']') {
        c.quadre--;
        
        if (last_text == '(' || last_text == '{') return false;
    }
    else if (*(text + i) == '}') {
        c.graffe--;
        
        if (last_text == '(' || last_text == '[') return false;
    }

    if (c.tonde < 0 || c.quadre < 0 || c.graffe < 0) return false;
}

return c.tonde == 0 && c.quadre == 0 && c.graffe == 0; */