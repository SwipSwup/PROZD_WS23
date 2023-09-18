#include <stdio.h>

int main() {
    int hour, minute;
    scanf("%2d:%2d", &hour, &minute);

    printf("24h time: 12h time: ");

    if (!hour) {
        printf("12:%d AM", minute);
        return 0;
    }

    if(hour < 13) {
        printf("%d:%d %s", hour, minute, hour < 12 ? "AM" : "PM");
        return 0;
    }

    printf("%2d:%d %s", hour - 12, minute, hour == 24 ? "AM" : "PM");
    return 0;
}


