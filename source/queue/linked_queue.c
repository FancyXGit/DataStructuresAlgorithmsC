#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int elem;
    struct node *next;
} node;

typedef struct linkedQueue
{
    node *rear;  // 链表队列尾部，不断加元素
    node *front; // 链表队列头部，不断减元素
} linkedQueue;

void buildQueue(linkedQueue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(linkedQueue *queue)
{
    if (queue->front == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pushQueue(linkedQueue *queue, int num)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at function 'pushQueue'\n");
        return;
    }
    new_node->elem = num;
    new_node->next = NULL;
    if (isEmpty(queue))
    {
        queue->rear = new_node;
        queue->front = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

int popQueue(linkedQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("EmptyQueueException at function 'popQueue'\n");
        return 0;
    }
    if (queue->front == queue->rear)
    {
        int pop_elem = queue->front->elem;
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        return pop_elem;
    }
    node *to_pop = queue->front;
    int to_pop_elem = queue->front->elem;
    queue->front = queue->front->next;
    free(to_pop);
    return to_pop_elem;
}

int getTop(linkedQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("EmptyQueueException at function 'getTop'\n");
        return 0;
    }
    return queue->front->elem;
}

void freeQueue(linkedQueue *queue)
{
    node *curr = queue->front;
    while (curr != NULL)
    {
        node *to_del = curr;
        curr = curr->next;
        free(to_del);
    }
    queue->front = NULL;
    queue->rear = NULL;
}

int main()
{
    linkedQueue queue;
    buildQueue(&queue);

    // 测试入队
    pushQueue(&queue, 10);
    pushQueue(&queue, 20);
    pushQueue(&queue, 30);

    printf("当前队头元素: %d\n", getTop(&queue)); // 应输出10

    // 测试出队
    printf("出队元素: %d\n", popQueue(&queue));     // 应输出10
    printf("出队后队头元素: %d\n", getTop(&queue)); // 应输出20

    // 测试空队列
    popQueue(&queue);
    popQueue(&queue);
    popQueue(&queue); // 再次出队，应该提示空队列异常

    // 测试多次入队
    for (int i = 0; i < 5; i++)
    {
        pushQueue(&queue, i * 100);
    }
    printf("再次入队后队头元素: %d\n", getTop(&queue)); // 应输出0

    // 释放队列空间
    freeQueue(&queue);

    return 0;
}