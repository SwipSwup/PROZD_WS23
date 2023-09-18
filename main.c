#include <stdio.h>

int main() {
    char time24[3];
    int hour;
    scanf("%2d:%2s", &hour, &time24[0]);

    printf("24h time: 12h time: ");

    if (!hour) {
        printf("12:%c%c AM", time24[0], time24[1]);
        return 0;
    }

    if(hour < 13) {
        printf("%d:%s %s", hour, time24, hour < 12 ? "AM" : "PM");
        return 0;
    }

    printf("%2d:%c%c %s", hour - 12, time24[0], time24[1], hour == 24 ? "AM" : "PM");
    return 0;
}


