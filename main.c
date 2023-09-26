#include <stdio.h>

int main() {
    int input;
    int grades[3];

    printf("Noten: ");
    scanf("%d", &input);

    for (int i = 0; i < 4; ++i) {
        if((i != 3 && !input) || (i == 3 && input)) {
            printf("Erwarte genau 3 Noten!");
            return 0;
        }

        if(i != 3) {
            grades[2 - i] = input % 10;
            input /= 10;
        }
    }

    int gSum = 0;
    for (int i = 0; i < 3; ++i) {
        if (grades[i] < 1 || grades[i] > 5) {
            switch (i) {
                case 0:
                    printf("Erste Note muss zwischen 1 und 5 liegen!");
                    return 0;
                case 1:
                    printf("Zweite Note muss zwischen 1 und 5 liegen!");
                    return 0;
                case 2:
                    printf("Dritte Note muss zwischen 1 und 5 liegen!");
                    return 0;
            }

        }

        if (grades[i] == 5) {
            printf("Nicht bestanden!");
            return 0;
        }

        gSum += grades[i];
    }

    switch (gSum) {
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
