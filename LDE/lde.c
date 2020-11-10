#include <stdio.h>
#include <ctype.h>

int main(void) {
    int ch  = getchar();
    while(ch != EOF) {
        if (isdigit(ch)) {
            int num = ch - '0';
            ch = getchar();
            if (ch == EOF) {
                break;
            }
            for (int i = 0;i < num; ++i){
                putchar(ch);
            }
        } else {
            putchar(ch);
        }
       ch = getchar();
    }
}
