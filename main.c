#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char time24[6];
    scanf("%5s", &time24);

    int hour = (time24[0] - 48) * 10 + time24[1] - 48;

    if(hour <= 12) {
        printf("%s AM", time24);
        return 0;
    }

    printf("%d:%c%c PM", );

    return 0;
}


