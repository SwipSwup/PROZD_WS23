#include <stdio.h>
#include <string.h>

#define VALID_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmonpqrstuvwxyz. \n"

int getNextChar(char *c)
{
    scanf("%c", c);
    return *c != '\0';
}

int validateChar(char *c)
{
    //printf("%c: %d", *c, strchr(VALID_CHARACTERS, *c) != NULL);
    return strchr(VALID_CHARACTERS, *c) != NULL;
}

int main()
{
    char nextChar;
    int sentenceLength = 1, wordLength = 0;
    int wordLengths[79] = {0};

    printf(": ");

    while (1)
    {
        getNextChar(&nextChar);

        if (!validateChar(&nextChar) || sentenceLength > 80 || (sentenceLength == 80 && nextChar != '.'))
        {
            printf("NOT VALID");
            return 1;
        }

        switch (nextChar)
        {
            case ' ':
            case '.':
            {
                if (wordLength != 0)
                {
                    wordLengths[wordLength]++;
                    wordLength = 0;
                }

                if (nextChar == '.')
                {
                    break;
                }
                break;
            }
            default:
            {
                wordLength++;
            }

        }

        sentenceLength++;

        if (nextChar == '.')
        {
            break;
        }
    }

    for (int i = 0; i < 79; ++i)
    {
        if (wordLengths[i])
        {
            printf("Length %d: %d\n", i, wordLengths[i]);
        }
    }

    return 0;
}

