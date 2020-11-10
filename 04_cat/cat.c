#include <stdio.h>

int main(void) {
    int str;
    while ((str = getchar()) != EOF) {
        putchar(str);
    }
    return 0;
}
