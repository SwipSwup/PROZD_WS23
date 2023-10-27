#include <stdio.h>
#include <malloc.h>

struct node
{
    int number;
    struct node* head;
} typedef node;

node* createNode(node* head)
{
    node* nodePtr = (node*) malloc(sizeof(node));
    nodePtr->head = head;

    return nodePtr;
}

node* get(int index, node* node)
{
    for (int i = 0; i < index; ++i, node = node->head);
    return node;
}

node* addBefore(int number, node* head)
{
    node* nodePtr = createNode(head);
    nodePtr->number = number;

    return nodePtr;
}

int size(node* node)
{
    int i = 0;
    for (; node != NULL; ++i, node = node->head);

    return i;
}

node* addAfter(int number, node* node)
{
    struct node* nodePtr = createNode(NULL);
    nodePtr->number = number;

    if (node != NULL)
    {
        get(size(node) - 1, node)->head = nodePtr;
        return node;
    }

    return nodePtr;
}


node* deleteAt(int index, node* node)
{
    if (index > size(node) - 1)
    {
        return node;
    }


    if (index == 0)
    {
        struct node* head = get(index, node)->head;
        free(node);
        return head;
    }

    struct node* nodeAtIndex = get(index, node);

    get(index - 1, node)->head = nodeAtIndex->head;
    free(nodeAtIndex);
    return node;
}

void freeFromNode(node* node)
{
    if (node == NULL)
        return;

    freeFromNode(node->head);
    free(node);
}

void printFromNode(node* node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%d ", node->number);
    printFromNode(node->head);
}

int main()
{
    int i = 0;
    node* node = NULL;

    while (1)
    {
        scanf(" %d", &i);
        if (!i)
        {
            break;
        }
        node = addAfter(i, node);
    }
    printFromNode(node);
    printf("\n");

    while (1)
    {
        scanf(" %d", &i);
        if (i < 0)
        {
            break;
        }

        node = deleteAt(i, node);
        printFromNode(node);
        printf("\n");

    }
    freeFromNode(node);

    return 0;
}
