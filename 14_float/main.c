#include <stdio.h>

void calculate(double x, double y, double* res);

int main(void) {
    double x, y, res;
    scanf("%lf %lf", &x, &y);
    calculate(x, y, &res);
    printf("%f\n", res);
}
