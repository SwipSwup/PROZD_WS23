#include <stdio.h>
#include <malloc.h>

struct node
{
    int height;
    int index;
    struct node* next;
    struct node* previous;
} typedef node;

node* createNode(int height)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->height = height;
    newNode->index = 0;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

node* addNode(node* newNode, node* list)
{
    newNode->next = list;
    if (list != NULL)
    {
        newNode->index = list->index + 1;
    }
    return newNode;
}

void updateList(int newHeight, node* list)
{
    if (list == NULL || list->next == NULL)
    {
        return;
    }

    if (list->next->height <= newHeight)
    {
        node* tmp = list->next;
        list->next = list->next->next;
        free(tmp);
        updateList(newHeight, list);
    }
}

void printList(node* list)
{
    if (list == NULL)
    {
        return;
    }

    printList(list->next);
    printf("%d [%d] ", list->height, list->index);

}

void freeAll(node* list)
{
    if (list == NULL)
    {
        return;
    }

    freeAll(list->next);
    free(list);
}

int main()
{
    node* list = NULL;

    int nextHeight;

    while (1)
    {
        printf(": ");
        scanf(" %d", &nextHeight);
        if (!nextHeight)
        {
            break;
        }

        list = addNode(createNode(nextHeight), list);
        updateList(list->height, list);
        printList(list);
        printf("\n");
    }
    printList(list);
    freeAll(list);
    return 0;
}
