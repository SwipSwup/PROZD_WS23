#include <stdio.h>

int main() {
    char time24[6];
    scanf("%5s", &time24[0]);

    int hour = (time24[0] - 48) * 10 + time24[1] - 48;
    printf("24h time: 12h time: ");

    if (!hour) {
        printf("12:%c%c AM", time24[3], time24[4]);
        return 0;
    }

    if(hour < 13) {
        printf("%s %s", time24, hour < 12 ? "AM" : "PM");
        return 0;
    }

    printf("%2d:%c%c %s", hour - 12, time24[3], time24[4], hour == 24 ? "AM" : "PM");
    return 0;
}


