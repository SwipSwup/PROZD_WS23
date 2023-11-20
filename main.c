#include <stdio.h>
#include <malloc.h>

struct node
{
    char customerId;
    struct node* next;
} typedef node;

node* createNode(char costumerId)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->customerId = costumerId;
    newNode->next = NULL;
    return newNode;
}

node* addNode(char customerId, node* list)
{
    node* newNode = createNode(customerId);

    if (list == NULL)
    {
        return newNode;
    }

    newNode->next = list;
    return newNode;
}

void removeNode(char customerId, node* list)
{
    if (list == NULL)
    {
        return;
    }
}

int main()
{
    node* customerList = NULL;
    node* registerOne = NULL;
    node* registerTwo = NULL;

    while (1)
    {
        char nextCustomerId;
        printf(": ");
        scanf(" %c", &nextCustomerId);

        if (nextCustomerId == '-') break;

        customerList = addNode(nextCustomerId, customerList);
    }

    int run = 1;
    while (run)
    {
        // Print here


        char c;
        printf(": ");
        scanf(" %c", &c);

        if (c == '-') break;

        switch (c)
        {
            case '-':
                run = 0;
                break;
            case 'a':
                // anstellen
                break;
            case '1':
                // kassa1
                break;
            case '2':
                // kassa2
                break;
        }
    }

    // free customerList

    return 0;
}
