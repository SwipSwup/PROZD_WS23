#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

char* scanText()
{
    char nextChar;
    char* text = (char*) malloc(sizeof (char) * 1001);
    int i = 0;

    while (1)
    {
        scanf("%c", &nextChar);

        if (nextChar == '\n' || i > 1000)
        {
            break;
        }

        if(isalpha(nextChar) || isspace(nextChar)) {
            text[i++] = nextChar;
        }
    }

    text[i] = '\0';
    return text;
}

char** scanWords()
{
    char** words = (char**) calloc(1, sizeof(char*)), ** tmp;
    int i = 0;
    while (1)
    {
        char buf[81];
        scanf("%80s", buf);
        if (buf[0] == '-') break;
        if (NULL == (tmp = (char**) realloc(words, sizeof(char*) * (i + 2))))
        {
            printf("out of memory");
            break;
        }
        words = tmp;
        words[i] = (char*) calloc(strlen(buf) + 1, sizeof(char));
        strcpy(words[i], buf);
        i++;
    }
    words[i] = (char*) calloc(1, sizeof(char));
    return words;
}

int countWord(char* text, char* word)
{
    char tmp[strlen(text) + 1];
    strcpy(tmp, text);
    char* token = strtok(tmp, " ");
    int count = 0;

    while (token != NULL)
    {
        //printf("token: %s\n", token);
        //printf("word: %s\n", word);
        //printf("string: %s\n", text);
        if (strstr(token, word) != NULL)
        {
            count++;
        }

        token = strtok(NULL, " ");
    }

    return count;
}

void freeAll(char** strngs)
{
    for (int i = 0; strcmp(strngs[i], "") != 0; ++i)
    {
        free(strngs[i]);
    }
    free(strngs);
}

int main()
{
    printf("text: ");
    char* text = scanText();

    printf("words: ");
    char** words = scanWords();
    for (int i = 0; strcmp(words[i], "") != 0; ++i)
    {
        printf("\n%s: %d", words[i], countWord(text, words[i]));
    }

    freeAll(words);
    free(text);
    return 0;
}
