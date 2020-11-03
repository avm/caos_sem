#include <stdio.h>

int main(void) {
    int x = 0;
    while (scanf("%d", &x) == 1) {
        printf("%x\n", x);
    }
    return 0;
}
