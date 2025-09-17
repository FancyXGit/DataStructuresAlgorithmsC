#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int elem;
    struct node *next;
}node;

node* buildList()
{
    node *head;
    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    return head;
}

node* getTail(node *list_head)
{
    node *curr = list_head;
    node *tail;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    tail = curr;
    return tail;
}

int getSize(node *list_head)
{
    node *curr = list_head;
    int size = 0;
    while (curr->next != NULL)
    {
        curr = curr->next;
        size++;
    }
    return size;
}

int getValue(node *list_head,int pos)
{
    node *curr = list_head->next;
    for (int i = 0; i < pos; i++)
    {
        curr = curr->next;
    }
    return curr->elem;
}

void listAppend(node *list_head, int num)
{
    node *tail = getTail(list_head);
    node *new_note = (node *)malloc(sizeof(node));
    new_note->elem = num;
    new_note->next = NULL;
    tail->next = new_note;
}

void printList(node *list_head)
{
    node *curr = list_head->next;
    while (curr != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

void freeList(node *list_head)
{
    node *curr = list_head;
    node *next;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void clearList(node *list_begin)
{
    freeList(list_begin->next);
    list_begin->next = NULL;
}

int main(void)
{
    node *l1 = buildList();
    int people_num;
    scanf("%d", &people_num);
    for (int i = 0; i < people_num; i++)
    {
        listAppend(l1, i + 1);
    }
    node *l2 = buildList();
    int code;
    while (scanf("%d",&code) != EOF && code != 0)
    {
        for (int i = 0; i < getSize(l1); i++)
        {
            if ((i + 1) % code == 0)
            {
                listAppend(l2, getValue(l1, i));
            }
        }
        node *temp = l1;
        l1 = l2;
        l2 = temp;
        clearList(l2);
        printList(l1);
    }
    printList(l1);
}