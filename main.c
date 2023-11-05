#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct node
{
    unsigned int id;
    char* name;
    struct node* head;
} typedef node;

node* createNode(char* name)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->id = 0;
    newNode->name = (char*) malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    newNode->head = NULL;

    return newNode;
}

void addLast(node* newNode, node* list)
{
    if (list->head == NULL)
    {
        newNode->id = list->id + 1;
        list->head = newNode;
        return;
    }

    addLast(newNode, list->head);
}

void printList(node* list)
{
    if (list == NULL)
    {
        return;
    }

    printf("%d: %s\n", list->id, list->name);
    printList(list->head);
}

void freeAll(node* list) {
    if(list == NULL) {
        return;
    }

    freeAll(list->head);
    free(list->name);
    free(list);
}

int main()
{
    char name[51];
    node* list = NULL;

    while (1)
    {
        scanf("%50s", name);

        if (!strcmp(name, "exit"))
        {
            break;
        }

        if (list == NULL)
        {
            list = createNode(name);
        }
        else
        {
            addLast(createNode(name), list);
        }

        printList(list);
        printf("\n");
    }

    freeAll(list);
    return 0;
}
