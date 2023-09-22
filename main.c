#include <stdio.h>
#include <math.h>
#include <string.h.h>

int getPrimes(int n);

int main() {

    return 0;
}

int getPrimes(int n) {
    int k = (n - 1) / n;
    int indecies[k + 1];
    int nonePrimeCount;

    for (int i = 0; i < k + 1; ++i)
        indecies[i] = 1;

    for (int i = 1; i < sqrt(k); ++i) {
        int j = i;
        while (i + j + 2 * i * j){
            indecies[i + j + 2 * i * j] = 0;
            nonePrimeCount++;
            j++;
        }
    }

    int primes[nonePrimeCount];
    for (int i = 0; i < k + 1; ++i) {
        if()
    }

}