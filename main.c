#include <stdio.h>

int main() {
    int i;
    scanf("%d", &i);

    for (; i > -1; i--) {
        printf("%d ", i);
    }
    return 0;
}