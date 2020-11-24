#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct String {
    char* data;
    size_t length;
    size_t capacity;
};


void string_init(struct String* string, const char* initial) {
    size_t len = strlen(initial) + 1;
    string->data = malloc(sizeof(char) * len);
    if (string->data == NULL) {
        abort();
    }
    strncpy(string->data, initial, len);
    string->length = len;
    string->capacity = len;
}


void string_free(struct String* string) {
    free(string->data);
    string->data = NULL;
    string->length = 0;
    string->capacity = 0;
}



void string_append(struct String* string, int c) {
    if (string->capacity < string->length + 1) {
        string->capacity *= 2;
        string->data = realloc(string->data, string->capacity);
        if (string->data == NULL) {
            abort();
        }
    }
    ++string->length;
    string->data[string->length - 2] = c;
    string->data[string->length - 1] = '\0';
}


int main(void) {
    // hello\n -> olleh\n
    struct String string;
    string_init(&string, "");
    int ch;
    do {
        ch = getchar();
        if (ch == EOF || ch == '\n') {
            for (int i = string.length - 2; i > -1; --i) {
                putchar(string.data[i]);
            }
            putchar('\n');
            string.data[0] = '\0';
            string.length = 1;
        } else {
            string_append(&string, ch);
        }
    } while (ch != EOF);
    string_free(&string);
    return 0;
}
