#include <stdio.h>
#include <float.h>

int main() {
    int cnt = 0;
    double min = DBL_MAX, max = DBL_MIN, sum = 0, n;

    do {
        printf(": ");
        scanf("%lf", &n);

        if (n > 0) {
            cnt++;
            sum += n;

            if (n > max) {
                max = n;
            }
            if (n < min) {
                min = n;
            }
        }
    } while (n > 0);

    if (cnt == 0) {
        printf("no number entered");
        return 0;
    }

    printf("cnt: %d\n", cnt);
    printf("min: %.2lf\n", min);
    printf("max: %.2lf\n", max);
    printf("avg: %.2lf", sum / cnt);

    return 0;
}