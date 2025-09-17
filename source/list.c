#include <stdio.h>
#include <malloc.h>

typedef struct note
{
    int elem;
    struct note *next;
}note;

note* buildList()
{
    note *head;
    head = (note *)malloc(sizeof(note));
    head->next = NULL;
    return head;
}

note* getTail(note *list_head)
{
    note *curr = list_head;
    note *tail;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    tail = curr;
    return tail;
}

int getSize(note *list_head)
{
    note *curr = list_head;
    int size = 0;
    while (curr->next != NULL)
    {
        curr = curr->next;
        size++;
    }
    return size;
}

int getValue(note *list_head,int pos)
{
    note *curr = list_head->next;
    for (int i = 0; i < pos; i++)
    {
        curr = curr->next;
    }
    return curr->elem;
}

void listAppend(note *list_head, int num)
{
    note *tail = getTail(list_head);
    note *new_note = (note *)malloc(sizeof(note));
    new_note->elem = num;
    new_note->next = NULL;
    tail->next = new_note;
}

void printList(note *list_head)
{
    note *curr = list_head->next;
    while (curr != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

void delElemVal(note *list_head, int val)
{
    note *curr = list_head;
    while (curr->next != NULL)
    {
        if (curr->next->elem == val)
        {
            note *next_note = curr->next->next;
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

void delElemSeq(note *list_head, int seq)
{
    note *curr = list_head;
    for (int i = 0; i < seq; i++)
    {
        curr = curr->next;
    }
    note *to_del = curr->next;
    curr->next = to_del->next;
    free(to_del);
}

void insertElemSeq(note *list_head, int seq, int val)
{
    note *curr = list_head;
    for (int i = 0; i < seq; i++)
    {
        curr = curr->next;
    }
    note *new_note = (note *)malloc(sizeof(note));
    note *after_note = curr->next;
    curr->next = new_note;
    new_note->elem = val;
    new_note->next = after_note;
}

void freeList(note *list_head)
{
    note *curr = list_head;
    note *next;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void clearList(note *list_begin)
{
    freeList(list_begin->next);
    list_begin->next = NULL;
}

int main(void)
{
    note *l1 = buildList();
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