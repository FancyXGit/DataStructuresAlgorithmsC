#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct node{
    int exp;
    double coef;
    struct node *next;
} node;

node* buildList(void)
{
    node *head = (node *)malloc(sizeof(node));
    head->next = NULL;
    return head;
}

node* getListTail(node* l)
{
    node *curr = l;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    return curr;
}

int isListEmpty(node *l)
{
    if (l->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void appendList(node* l,int new_exp, double new_coef)
{
    node *tail = getListTail(l);
    node *new_node = (node *)malloc(sizeof(node));
    new_node->exp = new_exp;
    new_node->coef = new_coef;
    new_node->next = NULL;
    tail->next = new_node;
}

void printList(node *l)
{
    node *head = l;
    node *curr = head->next;
    while (curr != NULL)
    {
        printf("%d %f\n", curr->exp, curr->coef);
        curr = curr->next;
    }
}

void addElem(node* l,int new_exp,double new_coef)
{
    if (isListEmpty(l))
    {
        appendList(l, new_exp, new_coef);
    }
    else
    {
        node *curr = l->next;
        node *prev = l;
        while (curr != NULL && curr->exp > new_exp)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL)
        {
            appendList(l, new_exp, new_coef);
        }
        else if (curr->exp == new_exp)
        {
            curr->coef += new_coef;
        }
        else
        {
            node *new_node = (node *)malloc(sizeof(node));
            new_node->coef = new_coef;
            new_node->exp = new_exp;
            new_node->next = curr;
            prev->next = new_node;
        }
    }
}

void AddList(node *l1, node *l2, node *sum)
{
    node *curr_l1 = l1->next;
    node *curr_l2 = l2->next;
    while (curr_l1 != NULL)
    {
        curr_l2 = l2->next;
        while (curr_l2 != NULL)
        {
            if (curr_l2->exp == curr_l1->exp)
            {
                addElem(sum, curr_l2->exp, curr_l2->coef + curr_l1->coef);
            }
            curr_l2 = curr_l2->next;
        }
        curr_l1 = curr_l1->next;
    }
    curr_l2 = l2->next;
    while (curr_l2 != NULL)
    {
        curr_l1 = l1->next;
        int flag = 1;
        while (curr_l1 != NULL)
        {
            if (curr_l2->exp == curr_l1->exp)
            {
                flag = 0;
            }
            curr_l1 = curr_l1->next;
        }
        if (flag == 1)
        {
            addElem(sum, curr_l2->exp, curr_l2->coef);
        }
        curr_l2 = curr_l2->next;
    }
    node *curr = sum->next;
    node *prev = sum;
    while (curr != NULL)
    {
        if (fabs(curr->coef) < 1e-5)
        {
            node *to_del = curr;
            prev->next = to_del->next;
            curr = curr->next;
            free(to_del);
        }
        else
        {
            curr = curr->next;
            prev = prev->next;
        }
    }
}

int main(void)
{
    node *l1 = buildList();
    node *l2 = buildList();
    double coef;
    int exp;
    while (1)
    {
        scanf("%lf %d", &coef, &exp);
        addElem(l1, exp, coef);
        if (getchar() == '\n')
        {
            break;
        }
    }
    while (1)
    {
        scanf("%lf %d", &coef, &exp);
        addElem(l2, exp, coef);
        if (getchar() == '\n')
        {
            break;
        }
    }

    node *sum = buildList();
    AddList(l1, l2, sum);
    //printList(sum);

    int seq;
    scanf("%d", &seq);
    node *curr = sum;
    for (int i = 0; i < seq; i++)
    {
        curr = curr->next;
    }
    printf("%.1f %d", curr->coef, curr->exp);
}