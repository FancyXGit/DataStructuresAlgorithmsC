#include <stdio.h>
#include <malloc.h>

typedef struct node{
    struct node *prev;
    int elem;
    struct node *next;
} node;

node* buildTwoHeadList()
{
    node *head = (node *)malloc(sizeof(node));
    head->prev = NULL;
    head->next = NULL;
    return head;
}

node* findListTail(node *list)
{
    node *curr = list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    return curr;
}

int isEmpty(node *list)
{
    return (list->next == NULL);
}

void appendTwoHeadList(node *list, int new_val)
{
    node *new_node = (node *)malloc(sizeof(node));
    node *tail = findListTail(list);
    new_node->elem = new_val;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = NULL;
}

void appendReverse(node *list, int val)
{
    if (isEmpty(list))
    {
        appendTwoHeadList(list, val);
    }
    else
    {
        node *new_node = (node *)malloc(sizeof(node));
        new_node->prev = list;
        new_node->next = list->next;
        new_node->elem = val;
        list->next->prev = new_node;
        list->next = new_node;
    }
}

void printTwoHeadList(node *list)
{
    node *curr = list->next;
    while (curr->next != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("%d", curr->elem);
}

node* mergeLists(node *list1, node *list2)
{
    node *curr1 = findListTail(list1);
    node *curr2 = findListTail(list2);
    node *merged = buildTwoHeadList();
    while (curr1 != list1 && curr2 != list2)
    {
        if (curr1->elem == curr1->prev->elem)
        {
            curr1 = curr1->prev;
            continue;
        }
        if (curr2->elem == curr2->prev->elem)
        {
            curr2 = curr2->prev;
            continue;
        }
        if (curr1->elem > curr2->elem)
        {
            appendReverse(merged, curr1->elem);
            curr1 = curr1->prev;
        }
        else if (curr1->elem < curr2->elem)
        {
            appendReverse(merged, curr2->elem);
            curr2 = curr2->prev;
        }
        else
        {
            appendReverse(merged, curr1->elem);
            curr1 = curr1->prev;
            curr2 = curr2->prev;
        }
    }
    while (curr1 != list1)
    {
        appendReverse(merged, curr1->elem);
        curr1 = curr1->prev;
    }
    while (curr2 != list2)
    {
        appendReverse(merged, curr2->elem);
        curr2 = curr2->prev;
    }
    return merged;
}

void inputList(node *list)
{
    int num = 0;
    while (scanf("%d", &num))
    {
        appendTwoHeadList(list, num);
        if (getchar() == '\n')
        {
            break;
        }
    }
}

int main(void)
{
    node *list1 = buildTwoHeadList();
    node *list2 = buildTwoHeadList();
    inputList(list1);
    inputList(list2);
    node *res = mergeLists(list1, list2);
    printTwoHeadList(res);
}