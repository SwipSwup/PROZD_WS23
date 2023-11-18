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

void addNode(node* newNode, node* list)
{
    if (list->next == NULL)
    {
        list->next = newNode;
        newNode->index = list->index + 1;
        return;
    }

    if(list->next->height <= newNode->height) {
        list->next = list->next->next;
    }
    addNode(newNode, list->next);
}


int main()
{
    node* list = NULL;

    int nextHeight;

    while (1)
    {
        scanf(" %d", &nextHeight);
        if (!nextHeight)
        {
            break;
        }
        node* newNode = createNode(nextHeight);
        if (list == NULL)
        {
            list = newNode;
        }
        else
        {
            addNode(newNode, list);
            for (node* n = list; n != NULL; n = n->next)
            {
                printf("%d [%d] ", n->height, n->index);
            }
            printf("\n");
        }
    }

    return 0;
}
