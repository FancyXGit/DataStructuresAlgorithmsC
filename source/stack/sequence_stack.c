#include <stdio.h>
#include <malloc.h>

typedef struct seqStack
{
    int capacity;
    int size;
    int *base;
    int *top;
} seqStack;

// 注意，构建的栈是顺序栈，top指向最前面元素的前一位
void buildSeqStack(seqStack *stack, int capacity)
{
    int *base = (int *)malloc(capacity * sizeof(int));
    if (base == NULL)
    {
        printf("MEMORY ALLOCATION EXCEPTION(BUILDSEQSTACK)\n");
        return;
    }
    stack->base = base;
    stack->top = base;
    stack->capacity = capacity;
    stack->size = 0;
}

int isFull(seqStack *stack)
{
    if (stack->capacity == stack->size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(seqStack *stack)
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

void pushStack(seqStack *stack, int num)
{
    if (isFull(stack))
    {
        printf("STACK FULL EXCEPTION(PUSHBACK)\n");
        return;
    }

    *stack->top = num;
    stack->top++;
    stack->size++;
}

void popStack(seqStack *stack)
{
    if (isEmpty(stack))
    {
        printf("STACK EMPTY EXCEPTION(POPSTACK)\n");
        return;
    }
    stack->top--;
    stack->size--;
}

int getTop(seqStack *stack)
{
    if (isEmpty(stack))
    {
        printf("STACK EMPTY EXCEPTION(GETTOP)\n");
        return 0;
    }
    return *(stack->top - 1);
}

void freeStack(seqStack *stack)
{
    free(stack->base);
    stack->base = NULL;
    stack->capacity = 0;
    stack->size = 0;
    stack->top = NULL;
}

int main()
{
    seqStack stack;
    buildSeqStack(&stack, 5);

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

    // 测试满栈
    for (int i = 0; i < 6; i++)
    {
        pushStack(&stack, i * 100);
    }

    // 释放栈空间
    freeStack(&stack);

    return 0;
}