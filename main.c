#include <stdio.h>
#include <math.h>
#include <malloc.h>

int *getPrimes(int n);

int main() {

    int *primes = getPrimes(50);

    for (int i = 0; i < sizeof(primes); ++i) {
        printf("%d\n", primes[i]);
    }

    return 0;
}

int *getPrimes(int n) {
    int k = (n - 1) / 2;
    int indices[k + 1];
    int nonePrimeCount = 0;

    for (int i = 0; i < k + 1; ++i)
        indices[i] = 1;

    for (int i = 1; i < sqrt(k); ++i) {
        int j = i;
        while (i + j + 2 * i * j <= k) {
            //printf("non prime %d\n", i + j + 2 * i * j);

            indices[i + j + 2 * i * j] = 0;
            //nonePrimeCount++;
            j++;
        }
    }

    for (int i = 0; i < k + 1; ++i) {
        if(indices[i])
            printf("%d\n", i);
    }

    /**
     *  printf("prime count %d\n", k + 1 - nonePrimeCount);

    for (int i = 0, j = 0; i < k + 1; ++i) {
        if (indices[i])
            primes[j++] = 2 * i + 1;
    }
     */

    int *primes = malloc(sizeof (100));


    return primes;
}