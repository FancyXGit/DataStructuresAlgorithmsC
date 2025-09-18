#include <stdio.h>
#include <malloc.h>

typedef struct node{
    int val;
    struct node *next;
} node;

node* buildCircleList(int first_val)
{
    node *head = (node *)malloc(sizeof(node));
    head->next = head;
    head->val = first_val;
    return head;
}

node* getCircleTail(node *list)
{
    node *curr = list;
    while (curr->next != list)
    {
        curr = curr->next;
    }
    return curr;
}

void appendCircleList(node *list,int new_val)
{
    node *head = list;
    node *new_node = (node *)malloc(sizeof(node));
    node *tail = getCircleTail(list);
    tail->next = new_node;
    new_node->val = new_val;
    new_node->next = head;
}

void printCircleList(node *list)
{
    node *head = list;
    node *tail = getCircleTail(list);
    node *curr = head;
    do{
        printf("%d ", curr->val);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

void clearCircleList(node *list, int first_val)
{
    node *curr = list->next->next;
    node *prev = list->next;
    while (curr != list)
    {
        free(prev);
        prev = curr;
        curr = curr->next;
    }
    list->val = first_val;
    list->next = list;
}

int main(void)
{
    node *list1 = buildCircleList(0);
    appendCircleList(list1, 10);
    appendCircleList(list1, 20);
    appendCircleList(list1, 30);
    appendCircleList(list1, 40);
    printCircleList(list1);
    clearCircleList(list1, 20);
    printCircleList(list1);
}