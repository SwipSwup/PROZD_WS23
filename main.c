#include <stdio.h>


void selection_sort(int a[], int N)
{
    int i, j, min, t;
    for (i = 0; i < N - 1; i++)
    {
        printf("Step %d: ", i + 1);

        min = i;

        for (j = i + 1; j < N; j++) // suche kleinstes El.
        {
            if (a[j] < a[min]) min = j; // merke Position des kleinsten El.
        }

        for (int k = 0; k < N; ++k)
        {
            if (k == min)
            {
                printf("[");
            }
            if (k == i)
            {
                printf("(");
            }
            printf("%d", a[k]);
            if (k == i)
            {
                printf(")");
            }
            if (k == min)
            {
                printf("]");
            }
            printf(" ");
        }
        t = a[min]; // Tausch
        a[min] = a[i];
        a[i] = t;

        printf("\n");
    }
}

int main()
{
    int numbers[1024];

    int size = 0, in;
    printf(": \n");
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

    printf("Result: ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n\nNumber of comparisons: %d", ((size - 1) * (size)) / 2);
    printf("\nNumber of swaps: %d", size - 1);
    return 0;
}
