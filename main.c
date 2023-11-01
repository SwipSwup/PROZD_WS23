#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct node
{
    char* word;
    int count;
    struct node* head;
} typedef node;

node* createNode(char* word, node* head)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->head = head == NULL ? NULL : head;
    newNode->word = word;
    newNode->count = 1;
    return newNode;
}

int size(node* map)
{
    int i = 0;
    for (; map->head != NULL; i++, map = map->head);

    return i;
}


node* getNode(int index, node* map)
{
    node* node = map->head;

    if (index > size(map) || index < 0)
    {
        return NULL;
    }

    if (!index)
    {
        return node;
    }

    for (int i = 0; i < index - 1; ++i)
    {
        node = node->head;
    }
    return node;
}

int nodeExists(char* word, node* map)
{
    if (!strcmp(word, map->word))
    {
        return 1;
    }

    if (map->head == NULL)
    {
        return 0;
    }

    return nodeExists(word, map->head);
}

void updateNode()
{

}

void addNode(node* newNode, node* map)
{
    if (map->head == NULL)
    {
        map->head = newNode;
        return;
    }

    addNode(newNode, map->head);
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
    node* map = NULL;

    char* nextWord = NULL;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] < 'a' || text[i] > 'z' || text[i] < 'A' || text[i] > 'Z')
        {
            if (nextWord == NULL)
                continue;

            if (nodeExists(word, map))
            {
                updateNode()
            }
            else
            {
                node* newNode = createNode(nextWord, map);

                addNode()
            }

            nextWord == NULL;
        }
    }
}


int main()
{
    char text[1001];

    printf("text: ");
    scanf("%1000s", &text[0]);

    printf("\nwords: ");
    char** words = scanWords();
    for (int i = 0; strcmp(words[i], "") != 0; ++i)
    {
        printf("%s \n", words[i]);

    }

    return 0;
}
