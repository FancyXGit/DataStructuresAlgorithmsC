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

void delElemVal(node *list_head, int val)
{
    node *curr = list_head;
    while (curr->next != NULL)
    {
        if (curr->next->elem == val)
        {
            node *next_note = curr->next->next;
            free(curr->next);
            curr->next = next_note;
            break;
        }
        else
        {
            curr = curr->next;
        }
    }
}

void delElemSeq(node *list_head, int seq)
{
    node *curr = list_head;
    for (int i = 0; i < seq; i++)
    {
        curr = curr->next;
    }
    node *to_del = curr->next;
    curr->next = to_del->next;
    free(to_del);
}

void insertElemSeq(node *list_head, int seq, int val)
{
    node *curr = list_head;
    for (int i = 0; i < seq; i++)
    {
        curr = curr->next;
    }
    node *new_note = (node *)malloc(sizeof(node));
    node *after_note = curr->next;
    curr->next = new_note;
    new_note->elem = val;
    new_note->next = after_note;
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
    for (int i = 0; i < 20; i++)
    {
        listAppend(l1, i + 1);
    }
    printList(l1);
    delElemVal(l1, 1);
    printList(l1);
    insertElemSeq(l1, 19, 10);
    printList(l1);
    delElemSeq(l1, 19);
    printList(l1);
}