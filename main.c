#include <stdio.h>

int main() {
    int i;

    scanf("%d", &i);

    if (i < 0 || i > 100) {
        printf("Ungueltige Punktezahl");
        return 0;
    }

    if (i > 90)
        printf("Sehr gut");
    else if (i > 76)
        printf("Gut");
    else if (i > 63)
        printf("Befriedigend");
    else if (i >= 50)
        printf("Genuegend");
    else
        printf("Nicht genuegend");

    return 0;
}
