#include <stdio.h>
#include <ctype.h>

int main(void) {
    int ch, count = 0;
    while((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            count = count * 10 + (ch - '0');
        } else {
            if (count == 0) {
                putchar(ch);
            } else {
                for (int i = 0; i < count; ++i) {
                    putchar(ch);
                }
                count = 0;
            }
        }
    }
}
