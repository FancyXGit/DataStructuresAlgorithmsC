#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int elem;
    struct node *next;
} node;

typedef struct linkedStack
{
    int size;
    node *top;
} linkedStack;

void buildStack(linkedStack *stack)
{
    stack->size = 0;
    stack->top = NULL;
}

int isEmpty(linkedStack *stack)
{
    if (stack->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pushStack(linkedStack *stack, int num)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("MemoryAllocationException at func 'pushStack'\n");
        return;
    }
    if (isEmpty(stack))
    {
        new_node->elem = num;
        new_node->next = NULL;
        stack->top = new_node;
        stack->size++;
    }
    else
    {
        new_node->elem = num;
        new_node->next = stack->top;
        stack->top = new_node;
        stack->size++;
    }
}

void popStack(linkedStack *stack)
{
    if (isEmpty(stack))
    {
        printf("EmptyStackException at func 'popStack'\n");
        return;
    }
    node *to_del = stack->top;
    stack->top = stack->top->next;
    free(to_del);
    to_del = NULL;
    stack->size--;
}

int getTop(linkedStack *stack)
{
    if (isEmpty(stack))
    {
        printf("EmptyStackException at func 'getTop'\n");
        return 0;
    }
    return stack->top->elem;
}

void freeStack(linkedStack *stack)
{
    node *curr = stack->top;
    node *to_del = curr;
    while (curr != NULL)
    {
        to_del = curr;
        curr = curr->next;
        free(to_del);
    }
    stack->size = 0;
    stack->top = NULL;
}

int main()
{
    linkedStack stack;
    buildStack(&stack);

    // 测试入栈
    pushStack(&stack, 10);
    pushStack(&stack, 20);
    pushStack(&stack, 30);

    printf("当前栈顶元素: %d\n", getTop(&stack)); // 应输出30

    // 测试出栈
    popStack(&stack);
    printf("出栈后栈顶元素: %d\n", getTop(&stack)); // 应输出20

    // 测试空栈
    popStack(&stack);
    popStack(&stack);
    popStack(&stack); // 再次出栈，应该提示空栈异常

    // 测试多次入栈
    for (int i = 0; i < 5; i++)
    {
        pushStack(&stack, i * 100);
    }
    printf("再次入栈后栈顶元素: %d\n", getTop(&stack)); // 应输出400

    // 释放栈空间
    freeStack(&stack);

    return 0;
}