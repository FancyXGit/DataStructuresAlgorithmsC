#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int elem;
    struct node *next;
} node;

// 所有的列表必须如下初始化，未初始化不得使用
// >>> list list1;
// >>> initList(&list1);
typedef struct list
{
    node *head;
    node *tail;
    int size;
} list;

// 所有的列表必须如下初始化，未初始化不得使用
// >>> list list1;
// >>> initList(&list1);
void initList(list *l)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at function 'initList'\n");
        return;
    }
    new_node->next = NULL;
    l->head = new_node;
    l->tail = new_node;
    l->size = 0;
}

// 链表是否为空
// >>> isEmpty(&list1)
int isEmpty(list *l)
{
    return l->head == l->tail;
}

// 在列表尾部添加元素n
// >>> append(&list1, n);
void appendList(list *l, int elem)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at function 'appendList'\n");
        return;
    }
    new_node->next = NULL;
    new_node->elem = elem;
    l->tail->next = new_node;
    l->tail = new_node;
    l->size++;
}

// 在链表头部插入元素
// >>> insertBeforeFirst(&list1, elem)
void insertBeforeFirst(list *l, int elem)
{
    if (isEmpty(l))
    {
        appendList(l, elem);
        return;
    }
    node *first_node = l->head->next;
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at function 'insertBeforeFirst'\n");
        return;
    }
    new_node->elem = elem;
    new_node->next = first_node;
    l->head->next = new_node;
    l->size++;
}

// 获取列表长度
// >>> getLength(&list1);
int getLength(list *l)
{
    return l->size;
}

// 获取链表第n个元素
// >>> getElem(&list1, n)
int getElem(list *l, int n)
{
    int length = getLength(l);
    if (n >= length || n < 0)
    {
        printf("IndexOutOfBoundException at function 'getElem'\n");
        return 0;
    }
    node *curr = l->head->next;
    for (int i = 0; i < n; i++)
    {
        curr = curr->next;
    }
    return curr->elem;
}

// 在链表第n位之前插入元素
// >>> insertElem(&list1, index, elem)
void insertElem(list *l, int index, int elem)
{
    int length = getLength(l);
    if (index < 0 || index >= length)
    {
        printf("IndexOutOfBoundException at function 'insertElem'\n");
        return;
    }
    node *before = l->head;
    for (int i = 0; i < index; i++)
    {
        before = before->next;
    }
    node *after = before->next;
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at function 'insertElem'\n");
        return;
    }
    new_node->elem = elem;
    before->next = new_node;
    new_node->next = after;
    l->size++;
}

// 删除链表第n位元素
// 返回删除元素的值
// >>> popElem(&list1, 0)
int popElem(list *l, int index)
{
    int length = getLength(l);
    if (index < 0 || index >= length)
    {
        printf("IndexOutOfBoundException at function 'popElem'\n");
        return 0;
    }
    node *prev = l->head;
    for (int i = 0; i < index; i++)
    {
        prev = prev->next;
    }
    node *to_del = prev->next;
    prev->next = to_del->next;
    int val = to_del->elem;
    free(to_del);
    l->size--;
    return val;
}

// 删除链表尾部元素
// 返回删除元素的值
// >>> popTail(&list1)
int popTail(list *l)
{
    if (isEmpty(l))
    {
        return 0;
    }
    node *curr = l->head;
    while (curr->next != l->tail)
    {
        curr = curr->next;
    }
    curr->next = NULL;
    int val = l->tail->elem;
    free(l->tail);
    l->tail = curr;
    l->size--;
    return val;
}

// 返回链表中值为elem的元素序号
// 找不到返回-1
// >>> getIndex(&list1, 0)
int getIndex(list *l, int elem)
{
    if (isEmpty(l))
    {
        return -1;
    }
    node *curr = l->head;
    int index = -1;
    while (curr != NULL)
    {
        curr = curr->next;
        index++;
        if (curr->elem == elem)
        {
            return index;
        }
    }
    return -1;
}

// 打印链表所有元素
// printList(&list1)
void printList(list *l)
{
    if (isEmpty(l))
    {
        printf("Empty List\n");
        return;
    }
    node *curr = l->head->next;
    while (curr != NULL)
    {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

// 清空链表所有元素
// 头节点未变，链表可以继续使用
// clearList(&list1)
void clearList(list *l)
{
    if (isEmpty(l))
    {
        return;
    }
    node *curr = l->head->next;
    while (curr != NULL)
    {
        node *to_del = curr;
        curr = curr->next;
        free(to_del);
    }
    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}

// 完全删除链表
// destoryList(&list1)
void destoryList(list *l)
{
    node *curr = l->head;
    while (curr != NULL)
    {
        node *to_del = curr;
        curr = curr->next;
        free(to_del);
    }
    l->head = NULL;
    l->size = -1;
    l->tail = NULL;
}

int main()
{
    list l;
    initList(&l);

    // 测试插入
    appendList(&l, 10);
    appendList(&l, 20);
    appendList(&l, 30);
    printList(&l); // 10 20 30

    insertBeforeFirst(&l, 5);
    printList(&l); // 5 10 20 30

    insertElem(&l, 2, 15);
    printList(&l); // 5 10 15 20 30

    printf("链表长度: %d\n", getLength(&l)); // 5

    // 测试查找
    printf("第3个元素: %d\n", getElem(&l, 2));      // 15
    printf("元素20的下标: %d\n", getIndex(&l, 20)); // 3

    // 测试删除
    printf("删除第2个元素: %d\n", popElem(&l, 1)); // 10
    printList(&l);                                 // 5 15 20 30

    printf("删除尾部元素: %d\n", popTail(&l)); // 30
    printList(&l);                             // 5 15 20

    // 测试清空
    clearList(&l);
    printList(&l); // Empty List

    // 测试销毁
    destoryList(&l);

    return 0;
}
