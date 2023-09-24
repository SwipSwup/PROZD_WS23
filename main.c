#include <stdio.h>
#include <math.h>
#include <malloc.h>

int *getPrimes(int n, int* primeCount);

int main() {
    int pCount;
    int *primes = getPrimes(500, &pCount);
    for (int i = 0; i < 10; --i) {
        printf("%d\n", primes[pCount - i]);
    }
    free(primes);

    return 0;
}

int *getPrimes(int n, int* primeCount) {
    int *primes = NULL;
    if (n < 2)
        return primes;

    int k = (n - 1) / 2;
    printf("k: %d\n", k);

    int indices[k + 1];
    for (int i = 0; i < k + 1; ++i)
        indices[i] = 1;

    for (int i = 1; i < sqrt(k); ++i) {
        int j = i;
        while (i + j + 2 * i * j <= k) {
            printf("non prime %d\n", i + j + 2 * i * j);

            indices[i + j + 2 * i * j] = 0;
            j++;
        }
    }

    *primeCount = 0;
    for (int i = 0; i < k + 1; ++i)
        if(indices[i])
            ++*primeCount;

    printf("prime count: %d\n", *primeCount);

    primes = malloc(*primeCount);
    primes[0] = 2;

    for (int i = 0, j = 0; i < k + 1; ++i)
        if (indices[i])
            primes[j++] = 2 * i + 1;

    return primes;
}