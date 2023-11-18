#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct node
{
    char* text;
    struct node* next;
} typedef node;

node* list = NULL;

struct node* create(char* text)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->text = (char*) malloc(strlen(text) + 1);
    strcpy(newNode->text, text);
    newNode->next = NULL;
    return newNode;
}

void attach_back(struct node* node)
{
    if (list == NULL)
    {
        return;
    }

    for (struct node* n = list; 1; n = n->next)
    {
        if (n->next == NULL)
        {
            n->next = node;
            node->next = NULL;
            break;
        }
    }
}

struct node* new_node(char* text)
{
    node* newNode = create(text);
    if (list == NULL)
    {
        list = newNode;
    }
    else
    {
        attach_back(newNode);
    }
    return newNode;
}

struct node* detach_front()
{
    if (list == NULL)
    {
        return NULL;
    }

    node* tmp = list;
    list = list->next;
    return tmp;
}

void free_all()
{
    for (node* n = list; n != NULL;)
    {
        node* tmp = n;
        n = n->next;
        free(tmp->text);
        free(tmp);
    }
}

void rotate(int count)
{
    for (int i = 0; i < count; ++i)
    {
        attach_back(detach_front());
    }
}

void print()
{
    for (node* n = list; n != NULL; n = n->next)
    {
        printf("%s\n", n->text);
    }
}

int main()
{
    char buffer[100];
    int rot;

    do
    {
        scanf("%99s", buffer);
    } while ((buffer[0] != '-') && (NULL != new_node(buffer)));

    print();

    scanf("%d", &rot);
    rotate(rot);
    print();

    free_all();

    return 0;
}