#include <stdio.h>

int main() {
    int grades[3];
    int gSum = 0;

    for (int i = 0; i < 3; ++i) {
        printf("Noten: ");
        scanf("%1d", &grades[i]);
    }

    for (int i = 0; i < 3; ++i) {
        if(grades[i] == 5) {
            printf("Nicht bestanden!");
            return 0;
        }

        gSum += grades[i];
    }

    switch(gSum) {
        case 3:
            printf("Ausgezeichneter Erfolg!");
            break;
        case 4:
            printf("Guter Erfolg!");
            break;
        default:
            printf("Bestanden.");
    }

    return 0;
}
