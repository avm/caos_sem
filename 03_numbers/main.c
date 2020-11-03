#include <stdio.h>

int main(void) {
    int x = 0;
    while (scanf("%d", &x) == 1) {
        printf("%x\n", x);
        for (int i = sizeof(x) * 8; i > 0; --i) {
	    printf("%d", 1 << (i - 1) & x ? 1 : 0);
  	}
        printf("\n");
    }
    return 0;
}
