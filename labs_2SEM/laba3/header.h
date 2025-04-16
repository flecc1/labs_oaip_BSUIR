#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../../mylib/header_Lib.h"
#include <ctype.h>

#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define RESET  "\033[0m"

struct Stack
{
    char data;
    int pos;
    struct Stack *next;
};

struct Stack *StackInit(struct Stack *top, char data, int pos);
struct Stack *pop(struct Stack *top);
void showStack(struct Stack *top);
void peek(struct Stack *top);
int checkParentheses(const char *expr);
void freeMemory(char **expression);
void freeStack(struct Stack *stack);
char peek2(struct Stack *top);