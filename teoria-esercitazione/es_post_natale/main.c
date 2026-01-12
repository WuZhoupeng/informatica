#include <stdio.h>
#include <string.h>

void insertText (char** full_text, char* text, int* pos);
void addText(char** full_text, char* text);
void undo (char** full_text, char** prev_text);
void redo (char** full_text, char** prev_text);
void saveOnFile (const char** full_text, char* filename);

int main () {

}

void insertText (char** full_text, char* text, int* pos) {
    if (*full_text == NULL) {
        *full_text = text;
    }

    char* temp = *full_text;

    if (pos != NULL) {
        if (strlen(*full_text) < *pos) {
            for (int i = 0; (*full_text + i) != NULL; ++i) {}

            *full_text = text;

            return;
        }
        else {
            for (int i = strlen(*full_text); i > *pos; --i) {
                *(*full_text + i + 1) = *(*full_text + i);
            }
        }
    }
}

void addText(char** full_text, char *text) {

}

void undo (char** full_text, char** prev_text) {

}

void redo (char** full_text, char** prev_text) {

}

void saveOnFile (const char** full_text, char* filename) {
    
}