#include <stdio.h>

int main() {
    int i;
    scanf("%d", &i);

    switch(i) {
        case 1:
            printf("Sehr gut");
            break;
        case 2:
            printf("Gut");
            break;
        case 3:
            printf("Befriedigend");
            break;
        case 4:
            printf("Genuegend");
            break;
        case 5:
            printf("Nicht genuegend");
            break;
        default:
            printf("Ungueltige Note");
    }

    return 0;
}
