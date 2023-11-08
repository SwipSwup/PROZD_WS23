#include <stdio.h>
#include <ctype.h>

#define MAX_PALINDROME_LENGTH 40

int main()
{
    char nextChar;
    int palindromeLength = 0;
    char palindrome[MAX_PALINDROME_LENGTH];

    printf(": ");
    while (1)
    {
        scanf("%c", &nextChar);

        if (nextChar == '\n' || palindromeLength == MAX_PALINDROME_LENGTH)
        {
            break;
        }

        if (!isalpha(nextChar))
        {
            continue;
        }

        palindrome[palindromeLength] = (char) tolower(nextChar);
        palindromeLength++;
    }

    for (int i = 0; i < palindromeLength / 2; ++i)
    {
        if(palindrome[i] != palindrome[palindromeLength - 1 - i]) {
            printf("false");
            return 0;
        }
    }

    printf("true");
    return 0;
}
