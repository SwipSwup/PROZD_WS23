#include <stdio.h>

int main() {
    double tax;
    scanf("%lf", &tax);

    printf(": With tax: %.2lf", tax * 1.2);
    return 0;
}
