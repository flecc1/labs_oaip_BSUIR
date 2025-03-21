#include "header.h"

struct Stack *StackInit(struct Stack *top, char data, int pos)
{
    struct Stack *ptr = (struct Stack*)malloc(sizeof(struct Stack));
    ptr->data = data;
    ptr->pos = pos;
    ptr->next = top;
    return ptr;
}

struct Stack *pop(struct Stack *top)
{
    if(top == NULL)
    {
        return top;
    }
    struct Stack *ptr_next = top->next;
    free(top);
    return ptr_next;
}

void freeStack(struct Stack *stack)
{
    while (stack != NULL)
    {
        stack = pop(stack);
    }
}

void showStack(struct Stack *top)
{
    if(top == NULL)
    {
        printf("стэк пуст \n");
        return;
    }
    while(top)
    {
        printf("%с ", top->data);
        top = top->next;
    }
    printf("\n");
}

void peek(struct Stack *top)
{
    if(top == NULL)
    {
        printf("стэк пуст\n");
        return;
    }
    printf("%d\n", top->data);
}


char peek2(struct Stack *top) {
    if (top == NULL) {
        return '\0'; // Возвращает нулевой символ, если стек пуст
    }
    return top->data;
}

// Функция проверки правильности расстановки скобок с выводом позиции ошибки
int checkParentheses(const char *str) 
{
    struct Stack *stack = NULL;
    for (int i = 0; *(str + i)!= '\0'; i++)
    {
        char ch = *(str + i);
        // Если символ – открывающая скобка, помещаем её в стек вместе с позицией
        if (ch == '(' || ch == '[' || ch == '{')
        {
            stack = StackInit(stack, ch, i);
        }
        // Если символ – закрывающая скобка, проверяем соответствие с вершиной стека
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (stack == NULL)
            {
                printf(RED "Ошибка: закрывающая скобка '%c' на позиции %d не имеет соответствующей открывающей.\n" RESET, ch, i);
                return 0;
            }
            if ((ch == ')' && peek2(stack) != '(') || (ch == ']' && peek2(stack) != '[') || (ch == '}' && peek2(stack) != '{'))
            {
                printf(RED "Ошибка: скобка '%c' на позиции %d не соответствует открывающей '%c' на позиции %d.\n" RESET, 
                        ch, i, peek2(stack), stack->pos);
                freeStack(stack);
                return 0;
            }
            stack = pop(stack);
        }
    }
    if (stack != NULL)
    {
        printf(RED "Ошибка: открывающая скобка '%c' на позиции %d не закрыта.\n" RESET, stack->data, stack->pos);
        freeStack(stack);
        return 0;
    }
    freeStack(stack);
    return 1;
}


void freeMemory(char **expression)
{
    free(*expression);
    *expression = NULL;
}

