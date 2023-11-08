#include <stdio.h>
#include <math.h>
#include <malloc.h>

void printPrimes(int n)
{
    if (n < 2)
        return;

    int k = (n - 1) / 2;
    //printf("k: %d\n", k);

    int indices[k + 1];
    for (int i = 0; i < k + 1; ++i)
        indices[i] = 1;

    //for (int i = 1; i < sqrt(k); ++i) { CodeRunner kann sqrt nicht compilieren
    for (int i = 1; i < k - 1; ++i)
    {
        int j = i;
        while (i + j + 2 * i * j <= k)
        {
            //printf("non prime %d\n", i + j + 2 * i * j);

            indices[i + j + 2 * i * j] = 0;
            j++;
        }
    }

    printf("2 ");
    for (int i = 1, j = 1; i < k + 1; ++i)
    {
        if (indices[i])
        {
            printf("%d ", 2 * i + 1);

            if (++j == 10)
            {
                printf("\n");
                j = 0;
            }
        }
    }
}

int main()
{
    int n;
    printf(": ");
    scanf(" %d", &n);

    printPrimes(n);
    return 0;
}

