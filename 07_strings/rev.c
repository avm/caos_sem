#include "strings.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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
