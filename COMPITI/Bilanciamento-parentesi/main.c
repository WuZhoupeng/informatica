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