#include <stdio.h>

int main() {
    int i;
    scanf("%d", &i);

    for (; i <= 20; i += 2) {
        printf("%d ", i);
    }
    return 0;
}