#include <stdio.h>


void selection_sort(int a[], int N)
{
    int i, j, min, t;
    for (i = 0; i < N - 1; i++)
    {
        min = i;
        for (j = i + 1; j < N; j++) // suche kleinstes El.
        {
            if (a[j] < a[min]) min = j; // merke Position des kleinsten El.
        }
        t = a[min]; // Tausch
        a[min] = a[i];
        a[i] = t;
    }
}


int main()
{
    int numbers[1024];

    int i = 0, in;
    while (1)
    {
        scanf(" %d ", &in);
        if (!in)
        {
            break;
        }

        numbers[i++] = in;
    }

    selection_sort(numbers, i);

    printf("%d ");

    return 0;
}
