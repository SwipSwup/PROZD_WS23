#include <stdio.h>
#include <malloc.h>

struct node {
    int number;
    struct node *head;
} typedef node;

node *addBefore(int number, node *head) {
    node *_node = (node *) malloc(sizeof(node));
    _node->head = head;
    _node->number = number;

    return _node;
}

void freeFromNode(node *node) {
    if (node == NULL)
        return;

    freeFromNode(node->head);
    free(node);
}

void printFromNode(node *node) {
    if (node == NULL)
        return;
    printf("%d ", node->number);
    printFromNode(node->head);
}

int main() {
    int number = 0;
    node *node = NULL;

    while (1) {
        scanf(" %d", &number);
        if (!number) {
            break;
        }
        node = addBefore(number, node);
    }

    printFromNode(node);
    freeFromNode(node);

    return 0;
}
