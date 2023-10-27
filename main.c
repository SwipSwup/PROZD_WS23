#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct node
{
    char* word;
    int count;
    struct node* head;
} typedef node;

node* createNode(node* head)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->head = head == NULL ? NULL : head;
    return newNode;
}

int size(node* list)
{
    int i = 0;
    for (; list->head != NULL; i++, list = list->head);

    return i;
}


node* getNode(int index, node* list)
{
    node* node = list->head;

    if (index > size(list) || index < 0)
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

void addNode(node* newNode, node* list)
{
    if(list->head == NULL) {
        list->head == newNode;
        return;
    }

    addNode(newNode, list->head);
}

countWord

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


int main()
{
    char text[1001];
    char** words = scanWords();

    scanf("%1000s", &text[0]);


    for (int i = 0; strcmp(words[i], "") != 0; ++i)
    {
        printf("%d ", strcmp(words[i], " "));
        printf("%s ", words[i]);

    }

    printf("Hello, World!\n");
    return 0;
}
