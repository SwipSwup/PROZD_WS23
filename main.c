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

node* addNode(node* newNode, node* list)
{
    if (list == NULL)
    {
        return newNode;
    }

    node* n = list;
    for (; n->next != NULL; n = n->next);
    n->next = newNode;
    return list;
}

int getListLength(node* list)
{
    int i = 0;
    for (node* n = list; n != NULL; n = n->next, i++);
    return i;
}

node* removeFirstNode(node* list)
{
    if (list == NULL)
    {
        return NULL;
    }

    node* next = list->next;
    free(list);
    return next;
}

void printList(node* list, char* msg)
{
    printf("%s %d\n", msg, getListLength(list));

    for (node* n = list; n != NULL; n = n->next)
    {
        printf("%c ", n->customerId);
    }
    printf("\n");
}

void printBilla(node* customerList, node* registerOne, node* registerTwo)
{
    printList(customerList, "Personen:");
    printList(registerOne, "Kassa 1:");
    printList(registerTwo, "Kassa 2:");
}

void populateRegister(node* customer, node** registerOne, node** registerTwo)
{
    customer->next = NULL;
    if (getListLength(*registerOne) <= getListLength(*registerTwo))
    {
        *registerOne = addNode(customer, *registerOne);
    }
    else
    {
        *registerTwo = addNode(customer, *registerTwo);
    }
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
    node* customerList = NULL;
    node* registerOne = NULL;
    node* registerTwo = NULL;

    while (1)
    {
        char nextCustomerId;
        printf(": ");
        scanf(" %c", &nextCustomerId);

        if (nextCustomerId == '-') break;

        customerList = addNode(createNode(nextCustomerId), customerList);
    }

    int run = 1;
    while (run)
    {
        printBilla(customerList, registerOne, registerTwo);

        char c;
        printf(": ");
        scanf(" %c", &c);

        if (c == '-') break;

        switch (c)
        {
            case '-':
            {
                run = 0;
                break;
            }
            case 'a':
            {
                node* next = customerList->next;
                populateRegister(customerList, &registerOne, &registerTwo);
                customerList = next;
                break;
            }
            case '1':
            {
                registerOne = removeFirstNode(registerOne);
                break;
            }
            case '2':
            {
                registerTwo = removeFirstNode(registerTwo);
                break;
            }
        }
    }

    freeAll(customerList);
    freeAll(registerOne);
    freeAll(registerTwo);
    return 0;
}
