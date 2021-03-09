#include <dlfcn.h>
#include <stdio.h>

typedef double (*math_fun_t)(double);

int main(int argc, char* argv[]) {
    char* function_name = argv[1];
    
    void* libm = dlopen("/lib/libm.so.6", RTLD_LAZY);
    if (!libm) {
        perror("dlopen failed");
        return 1;
    }
    math_fun_t function = dlsym(libm, function_name);
    if (!function) {
        fprintf(stderr, "dlsym failed: %s\n", dlerror());
        return 1;
    }
    double val;
    while(scanf("%lf", &val) == 1) {
        double res = function(val);
        printf("%lf\n", res);
    }
    dlclose(libm);
}
