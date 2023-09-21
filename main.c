#include <stdio.h>

int main() {
    int i;

    while(1) {
        scanf("%d", &i);
        if(i >= 10) {
            printf("Abbruch");
            break;
        }

        printf("%d\n", i);
    }
    return 0;
}