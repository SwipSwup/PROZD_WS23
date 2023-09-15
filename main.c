#include <stdio.h>

int main() {
    int i, j;

    scanf("%d", &i);
    scanf("%d", &j);

    printf(i > 50 && i + j >= 70 ? "Positiv" : "Negativ");

    return 0;
}
