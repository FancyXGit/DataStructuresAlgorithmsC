#include <stdio.h>
#include <malloc.h>

typedef struct node{
    int elem;
    struct node *next;
} node;

node* buildList(void)
{
    node *head = (node *)malloc(sizeof(node));
    head->next = NULL;
    return head;
}

void appendList(node *list, int val)
{
    node *new_node = (node *)malloc(sizeof(node));
    node *curr = list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = new_node;
    new_node->elem = val;
    new_node->next = NULL;
}

void printList(node *list)
{
    node *curr = list->next;
    while (curr->next != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("%d\n", curr->elem);
}

node* findTail(node *list)
{
    node *curr = list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    return curr;
}

void findAndMoveMaxNode(node *list)
{
    node *curr = list->next;
    node *max_node = list->next;
    while (curr != NULL)
    {
        if (curr->elem > max_node->elem)
        {
            max_node = curr;
        }
        curr = curr->next;
    }
    node *prev_to_max = list;
    node *tail = findTail(list);
    while (prev_to_max->next != max_node)
    {
        prev_to_max = prev_to_max->next;
    }
    prev_to_max->next = max_node->next;
    tail->next = max_node;
    max_node->next = NULL;
}

int main(void)
{
    node *list = buildList();
    int num = 0;
    while (scanf("%d", &num))
    {
        appendList(list, num);
        if (getchar() == '\n')
        {
            break;
        }
    }
    findAndMoveMaxNode(list);
    printList(list);
}