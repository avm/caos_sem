#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            FILE *f = fopen(argv[i], "rb");
            if (!f) {
                fprintf(stderr, "fopen failed: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            int ch;
            while ((ch = fgetc(f)) != EOF) {
                putchar(ch);
            }
            fclose(f);
        }
    } else {
        int str;
        while ((str = getchar()) != EOF) {
            putchar(str);
        }
    }
    return 0;
}
