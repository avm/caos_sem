#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *str = argv[1];
    int str_size = strlen(str);
    char *last_slash = strrchr(str, '/');
    if (last_slash) {
        puts(++last_slash);
    } else {
        puts(str);
    }
    return 0;
}
