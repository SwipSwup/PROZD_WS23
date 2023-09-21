#include <stdio.h>

int main() {
    int i;

    do {
        printf("1. Continue\n"
               "2. Quit\n"
               "Your selection:\n");

        scanf("%d", &i);
        switch(i) {
            case 1:
                printf("Let's continue\n");
                break;
            case 2:
                printf("Bye, bye\n");
                break;
            default:
                printf("Unknown selection\n");
        }
    } while (i != 2);

    return 0;
}