#include <stdio.h>

int main() {
    int calenderLength, startingDayIndex;

    printf("number of days in month:");
    scanf("%d", &calenderLength);
    printf("\nstarting day of week (1=Monday, 7=Sunday):");
    scanf("%d", &startingDayIndex);

    for (int i = 0; i < calenderLength + startingDayIndex; ++i) {
        if(!(i % 7))
            printf("\n");

        if(i < startingDayIndex - 1)
            printf("   ");
        else
            printf("%2d ", i + 1 - startingDayIndex - 1);
    }

    return 0;
}
