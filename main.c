#include <stdio.h>

void getNextPermutation(int* permutation, int size)
{
    int suffixIndex = size - 1;
    for (int i = size - 1; i > 0 && permutation[i - 1] > permutation[i]; --i, --suffixIndex);

    for (int i = size - 1; i >= suffixIndex && suffixIndex != 0; --i)
    {
        if (permutation[i] > permutation[suffixIndex - 1])
        {
            int tmp = permutation[i];
            permutation[i] = permutation[suffixIndex - 1];
            permutation[suffixIndex - 1] = tmp;
            break;
        }
    }

    for (int i = 0; i < (size - suffixIndex) / 2; ++i)
    {
        int tmp = permutation[suffixIndex + i];
        permutation[suffixIndex + i] = permutation[size - 1 - i];
        permutation[size - 1 - i] = tmp;
    }
}

int main()
{
    int size;
    printf(": ");
    scanf(" %d", &size);

    printf(": ");
    int permutation[size];
    for (int i = 0; i < size; ++i)
    {
        scanf(" %d", &permutation[i]);
    }

    printf("\n");
    getNextPermutation(permutation, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", permutation[i]);
    }

    return 0;
}
