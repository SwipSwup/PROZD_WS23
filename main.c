#include <stdio.h>

int main() {
    char time24[3];
    int hour;
    scanf("%2d:%2s", &hour, &time24[0]);

    printf("24h time: 12h time: ");

    if (!hour) {
        printf("12:%s AM", time24);
        return 0;
    }

    if(hour < 13) {
        printf("%d:%s %s", hour, time24, hour < 12 ? "AM" : "PM");
        return 0;
    }

    printf("%2d:%s %s", hour - 12, time24, hour == 24 ? "AM" : "PM");
    return 0;
}


