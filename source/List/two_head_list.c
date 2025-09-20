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

void appendTwoHeadList(node *list, int new_val)
{
    node *new_node = (node *)malloc(sizeof(node));
    node *tail = findListTail(list);
    new_node->elem = new_val;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = NULL;
}

void printTwoHeadList(node *list)
{
    node *curr = list->next;
    while (curr != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

void delSelectNode(node *list, node *node_to_del)
{
    node *prev_del = node_to_del->prev;
    node *next_del = node_to_del->next;
    free(node_to_del);
    prev_del->next = next_del;
    next_del->prev = prev_del;
}

node* findElemNode(node *list, int val)
{
    node *curr = list;
    while (curr != NULL )
    {
        curr = curr->next;
        if (curr->elem == val)
        {
            return curr;
        }
    }
    printf("\n(from func 'findElemNode') NO SUCH VALUE FOUND\n");
    return NULL;
}

void delSelectElem(node *list, int val)
{
    delSelectNode(list, findElemNode(list, val));
}

void insertElemNode(node *list, node *insert_before, int val)
{
    node *new_node = (node *)malloc(sizeof(node));
    node *insert_after = insert_before->prev;
    insert_after->next = new_node;
    new_node->prev = insert_after;
    new_node->elem = val;
    new_node->next = insert_before;
    insert_before->prev = new_node;
}

void insertElemVal(node *list, int val_before_to_insert, int val)
{
    insertElemNode(list, findElemNode(list, val_before_to_insert), val);
}

int main(void)
{
    node *list = buildTwoHeadList();
    appendTwoHeadList(list, 10);
    appendTwoHeadList(list, 20);
    appendTwoHeadList(list, 30);
    appendTwoHeadList(list, 40);
    printTwoHeadList(list);
    delSelectElem(list, 20);
    printTwoHeadList(list);
    insertElemVal(list, 30, 20);
    printTwoHeadList(list);
}