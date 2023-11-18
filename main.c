#include <stdio.h>


void selection_sort(int a[], int N)
{
    int i, j, min, t;
    for (i = 0; i < N - 1; i++)
    {
        printf("Step %d: ", i);

        min = i;
        for (j = i + 1; j < N; j++) // suche kleinstes El.
        {
            if (a[j] < a[min]) min = j; // merke Position des kleinsten El.
        }
        t = a[min]; // Tausch
        a[min] = a[i];
        a[i] = t;
        for (int k = 0; k < N; ++k)
        {
            if(a[k] == t) {
                printf("(");
            }
            printf("%d", a[k]);
            if(a[k] == t) {
                printf(")");
            }
            printf(" ",);
        }
    }
}


int main()
{
    int numbers[1024];

    int size = 0, in;
    while (1)
    {
        scanf(" %d", &in);
        if (!in)
        {
            break;
        }

        numbers[size++] = in;
    }

    selection_sort(numbers, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", numbers[i]);
    }

    return 0;
}
