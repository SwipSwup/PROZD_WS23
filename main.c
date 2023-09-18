#include <stdio.h>

int main() {
    int hour, minute;
    scanf("%2d:%2d", &hour, &minute);

    printf("24h time: 12h time: ");

    if (!hour) {
        printf("12:%02d AM", minute);
        return 0;
    }

    if(hour < 13) {
        printf("%d:%02d %s", hour, minute, hour < 12 ? "AM" : "PM");
        return 0;
    }

    printf("%2d:%02d %s", hour - 12, minute, hour == 24 ? "AM" : "PM");
    return 0;
}


