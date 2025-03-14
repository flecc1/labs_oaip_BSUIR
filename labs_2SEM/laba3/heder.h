#pragma once

#include <stdio.h>
#include <stdlib.h>


struct Stack
{
    char data;
    struct Stack *next;
};


struct Stack *StackInit(struct Stack *top, char data)
{
    struct Stack *ptr = (struct Stack*)malloc(sizeof(struct Stack));
    ptr->data = data;
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



void showStack(struct Stack *top)
{
    if(top == NULL)
    {
        printf("стэк пуст \n");
        return;
    }
    while(top)
    {
        printf("%d ", top->data);
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