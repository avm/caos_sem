#include <time.h>
#include <stdio.h>

enum { seconds_in_day = 24 * 3600 };

int main() {
    time_t now = time(NULL);
    int datediff;
    while (scanf("%d", &datediff) == 1) {
        time_t datediff_time = datediff;
        time_t seconds_diff, result;
        if (__builtin_mul_overflow(datediff_time, seconds_in_day, &seconds_diff)
            || __builtin_add_overflow(now, seconds_diff, &result)) {
            printf("OVERFLOW\n");
        } else {
            struct tm* tm = localtime(&result);
            char buf[20];
            strftime(buf, 19, "%F", tm);
            printf("%s\n", buf);
        }
    }
}
