#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int(*puts_t)(char*);


int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "not enough args\n");
        return 1;
    }
    void* libm = dlopen(argv[1], RTLD_NOW);
    if (!libm) {
        perror("dlopen failed");
        return 1;
    }
    void* function = dlsym(libm, argv[2]);
    if (!function) {
        fprintf(stderr, "dlsym failed: %s\n", dlerror());
        return 1;
    }

    puts_t myputs = function;
    myputs(argv[4]);

    char* spec = argv[3];
    int spec_len = strlen(spec);

    char* args = calloc(8, spec_len);
    char* next_arg = args;
    for (int i = 1; i < spec_len; ++i) {
        char spec_char = spec[i];
        int int_arg;
        double double_arg;
        char* cmdline_arg = argv[i + 3];
        switch (spec_char) {
            case 'i':
                int_arg = strtol(argv[i+3], 0, 10);
                memcpy(next_arg, &int_arg, 4);
                next_arg += 4;
                break;
            case 'd':
                double_arg = strtod(argv[i+3], 0);
                memcpy(next_arg, &double_arg, 8);
                next_arg += 8;
                break;
            case 's':
                memcpy(next_arg, &cmdline_arg, 4);
                next_arg += 4;
                break;
            default:
                fprintf(stderr, "invalid spec char %c\n", spec_char);
                return 1;
        }
    }

    int result;

    int args_size = next_arg - args;
    asm volatile(
        "sub %[args_size], %%esp\n"
        "mov %%esp, %%eax\n"
        "push %[args_size]\n"
        "push %[args_source]\n"
        "push %%eax\n"
        "call memcpy\n"
        "add $12, %%esp\n"
        "mov %[function], %%eax\n"
        "call *%%eax\n"
        "mov %%eax, %[result]\n"
        "add %[args_size], %%esp"
        :
        [result] "+m" (result)
        :
        [args_size] "g" (args_size),
        [args_source] "g" (args),
        [function] "m" (function)
        :
        "%eax", "memory");

    printf("%d\n", result);
    dlclose(libm);
}
