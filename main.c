#include <stdio.h>

int main() {
    int n, i = 1, firstPos = 1, startPos = 1;

    do {
        printf(": ");
        scanf("%d", &n);

        i++;
        if (n != 0 && n <= startPos) {
            startPos++;
            printf("position #1: %d\n", startPos);
        }

        if (n == 1) {
            firstPos = i;
            printf("new leader: #%d\n", i);
        }
    } while (n != 0);

    printf("final position #1: %d\n", startPos);
    printf("winner: #%d", firstPos);
    return 0;
}
