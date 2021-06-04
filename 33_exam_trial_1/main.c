#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
// intmin / -1 = жопа
// деление на ноль
// 0 - название, дальше - аргументы <- это все в argv
    int val1 = strtol(argv[1], NULL, 9);
    int val2 = strtol(argv[2], NULL, 9);

// __builtin_add_overlow(one, two, result) = 1 если все плохо, 0 - если переполнения не было
// Второй вариант - конвертировать в int64 сложить и посмотреть что будет (>INT32MAX)
    int res;
    if (__builtin_add_overflow(val1, val2, &res)) {
        printf("1\n");
    } else { printf("0\n"); }


// Это для деления
    int res2;
    if ( (val2 == 0) || (val1 == INT32_MIN &&  val2 == -1) ) {
        printf("1\n");
    } else { printf("0\n"); }
}

