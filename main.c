#include <stdio.h>

int main() {
    int x, y;

    scanf("%d", &x);
    scanf("%d", &y);

    printf("%d\n", x = y + 5);
    printf("%d\n", y *= 3);
    printf("%d\n", x = y / 2);
    printf("%d\n", x % y);
    return 0;
}
