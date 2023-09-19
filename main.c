#include <stdio.h>

int main() {
    int n[5];

    scanf("%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
    int min = n[0], max = n[0];

    for (int i = 1; i < 5; ++i) {
        if (min > n[i])
            min = n[i];
        else if (max < n[i])
            max = n[i];
    }

    printf(": minimum sum: %d\n", n[0] + n[1] + n[2] + n[3] + n[4] - max);
    printf("maximum sum: %d", n[0] + n[1] + n[2] + n[3] + n[4] - min);

    return 0;
}
