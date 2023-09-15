#include <stdio.h>

int main() {
    int x, y;

    scanf("%d", &x);
    scanf("%d", &y);

    printf("%d\n",  x > 0 && x < y);
    printf("%d\n",  x == y || y < 0);
    printf("%d\n",  (!x || !y) && x != y);

    return 0;
}
