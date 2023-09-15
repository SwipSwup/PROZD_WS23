#include <stdio.h>

int main() {
    int i;

    scanf("%d", &i);

    if(i < 0 || i > 100) {
        printf("Ungültige Punktezahl");
        return 0;
    }

    printf("Gültige Punktezahl\n");
    printf(i >= 50 ? "Positive Note" : "Negative Note");
    return 0;
}
