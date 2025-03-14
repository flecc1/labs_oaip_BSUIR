#pragma once

#include <stdio.h>
#include <stdlib.h>


struct Stack
{
    char data;
    struct Stack *next;
};


struct Stack *StackInit(struct Stack *top, char data);
struct Stack *pop(struct Stack *top);
void showStack(struct Stack *top);
void peek(struct Stack *top);
