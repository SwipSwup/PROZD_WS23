#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void* a, const void* b)
{
    int int_a = *((int*) a);
    int int_b = *((int*) b);

    if (int_a > int_b)
    {
        return 1;
    }

    if (int_a < int_b)
    {
        return -1;
    }

    return 1;
}

int main()
{

    int size1, size2;

    printf(": ");
    scanf(" %d %d", &size1, &size2);

    int arr1[size1];
    int arr2[size2];

    printf("size1: %d\n", size1);
    printf("size2: %d\n", size2);

    for (int i = 0, val = 0; i < size1; ++i)
    {
        scanf("%d", &val);
        arr1[i] = val;
    }

    for (int i = 0, val = 0; i < size2; ++i)
    {
        scanf("%d", &val);
        arr2[i] = val;
    }

    qsort(arr1, size1, sizeof(int), compare);
    qsort(arr2, size2, sizeof(int), compare);

    //pair1, pair2, difference
    int pair[3] = {0, 0, INT_MAX};

    for (int i = size1 - 1; i >= 0; --i)
    {
        printf("i: %d\n", arr1[i]);
        printf("j: %d\n", arr2[0]);
        if (arr1[i] < arr2[0])
        {
            break;
        }

        for (int j = 0; j < size2; ++j)
        {

            if (arr1[i] < arr2[j])
            {
                break;
            }

            printf("i: %d\n", arr1[i]);
            printf("j: %d\n", arr2[j]);

            if (pair[2] > arr1[i] - arr2[j])
            {
                pair[0] = arr1[i];
                pair[1] = arr2[j];
                pair[2] = arr1[i] - arr2[j];
            }
        }
    }

    printf("%d (%d, %d)", pair[2], pair[0], pair[1]);

    return 0;
}
