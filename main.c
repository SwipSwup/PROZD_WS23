#include <stdio.h>

int main() {
    char c;

    do {
        printf("Abbrechen (j/n)?\n");
        scanf("%c", &c);
    } while (c != 'j');

    return 0;
}