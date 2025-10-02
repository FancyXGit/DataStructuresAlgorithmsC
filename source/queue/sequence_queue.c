#include <stdio.h>
#include <malloc.h>

typedef struct seqQueue
{
    int front;
    int rear;
    int capacity;
    int *queue_location;
} seqQueue;

void buildQueue(seqQueue *queue, int capacity)
{
    int *new_queue = (int *)malloc(capacity * sizeof(int));
    if (new_queue == NULL)
    {
        printf("MemoryAllocationException at function 'buildQueue'\n");
        return;
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->queue_location = new_queue;
}

int isFull(seqQueue *queue)
{
    if ((queue->rear + 1) % queue->capacity == queue->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pushQueue(seqQueue *queue, int num)
{
    if (isFull(queue))
    {
        printf("FullQueueException at function 'pushQueue'\n");
        return;
    }
    queue->queue_location[queue->rear] = num;
    queue->rear = (queue->rear + 1) % queue->capacity;
}

int isEmpty(seqQueue *queue)
{
    if (queue->rear == queue->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int popQueue(seqQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("EmptyQueueException at function 'popQueue'\n");
        return 0;
    }
    int to_pop = queue->queue_location[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    return to_pop;
}

int getFront(seqQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("EmptyQueueException at function 'getFront'\n");
        return 0;
    }
    return queue->queue_location[queue->front];
}

void freeQueue(seqQueue *queue)
{
    free(queue->queue_location);
    queue->queue_location = NULL;
    queue->capacity = 0;
    queue->front = 0;
    queue->rear = 0;
}

int main()
{
    seqQueue queue;
    buildQueue(&queue, 5);

    // 测试入队
    pushQueue(&queue, 10);
    pushQueue(&queue, 20);
    pushQueue(&queue, 30);

    printf("当前队头元素: %d\n", getFront(&queue)); // 应输出10

    // 测试出队
    printf("出队元素: %d\n", popQueue(&queue));       // 应输出10
    printf("出队后队头元素: %d\n", getFront(&queue)); // 应输出20

    // 测试空队列
    popQueue(&queue);
    popQueue(&queue);
    popQueue(&queue); // 再次出队，应该提示空队列异常

    // 测试满队列
    for (int i = 0; i < 5; i++)
    {
        pushQueue(&queue, i * 100);
    }
    pushQueue(&queue, 999); // 应提示队列已满

    // 释放队列空间
    freeQueue(&queue);

    return 0;
}