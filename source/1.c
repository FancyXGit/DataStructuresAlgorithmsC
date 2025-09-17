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
    int people_num;
    scanf("%d", &people_num);
    for (int i = 0; i < people_num; i++)
    {
        listAppend(l1, i + 1);
    }
    note *l2 = buildList();
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
        note *temp = l1;
        l1 = l2;
        l2 = temp;
        clearList(l2);
        printList(l1);
    }
    printList(l1);
}