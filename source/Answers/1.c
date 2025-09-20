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

node* delSelectElem(node *list, node *pos)
{
    if (pos == list)
    {
        node *tail = getCircleTail(list);
        node *new_head = list->next;
        free(list);
        tail->next = new_head;
        return new_head;
    }
    else
    {
        node *curr = list;
        while (curr->next != pos)
        {
            curr = curr->next;
        }
        curr->next = pos->next;
        free(pos);
        return list;
    }
}

node* doJosephus(node *list, node *new_list, int interval)
{
    node *curr1 = list;
    int count = 1;
    int first_add = 1;
    while (list->next != list)
    {
        node *next = curr1->next;
        if (count == interval)
        {
            if (first_add)
            {
                new_list->val = curr1->val;
                list = delSelectElem(list, curr1);
                curr1 = next;
                count = 1;
                first_add = 0;
            }
            else
            {
                appendCircleList(new_list, curr1->val);
                list = delSelectElem(list, curr1);
                curr1 = next;
                count = 1;
            }
        }
        else
        {
            curr1 = curr1->next;
            count++;
        }
    }
    appendCircleList(new_list, list->val);
    return list;
}

int main(void)
{
    int people_num = 0;
    scanf("%d", &people_num);
    node *l1 = buildCircleList(1);
    for (int i = 2; i <= people_num; i++)
    {
        appendCircleList(l1,i);
    }
    node *l2 = buildCircleList(0);
    int code = 0;
    while (scanf("%d",&code) != EOF && code != 0)
    {
        l1 = doJosephus(l1, l2, code);
        node *temp = l1;
        l1 = l2;
        l2 = temp;
        clearCircleList(l2, 0);
        if (getchar() == '\n')
        {
            break;
        }
    }
    printCircleList(l1);
}