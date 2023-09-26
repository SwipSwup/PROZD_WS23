#include <stdio.h>

int main() {
    int calenderLength, startingDayIndex;

    printf("number of days in month: ");
    scanf("%d", &calenderLength);
    printf("starting day of week (1=Monday, 7=Sunday):");
    scanf("%d", &startingDayIndex);

    for (int i = 1; i < calenderLength + startingDayIndex; ++i) {
        if(!((i - 1) % 7))
            printf("\n");

        if(i < startingDayIndex)
            printf("   ");
        else
            printf("%2d ", i - startingDayIndex + 1);
    }

    return 0;
}
