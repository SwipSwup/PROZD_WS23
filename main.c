#include <stdio.h>

int main() {
    int i;
    scanf("%d", &i);

    while(i <= 20) {
        printf("%d ", i);
        ++i;
    }
    return 0;
}