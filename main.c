#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct node
{
    unsigned int id;
    char* name;
    struct node* head;
} typedef node;

node* createNode(int id, char* name)
{
    node* newNode = (node*) malloc(sizeof(node*));
    newNode->id = id;
    newNode->name = name;
    newNode->head = NULL;

    return newNode;
}

node* addLast(node* newNode, node* list)
{
    if (list == NULL)
    {
        return newNode;
    }

    if (list->head)
    {
        list->head = newNode;
        return list;
    }

    return addLast(newNode, list->head);
}

int main()
{
    char name[51];

    while (1)
    {
        scanf("%50s", &name[0]);


        if (!strcmp(name, "exit"))
        {
            break;
        }
    }

    return 0;
}
