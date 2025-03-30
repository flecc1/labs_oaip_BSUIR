#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    Node *next;
};

struct Queue
{
    Node *head;
    Node *end;
};

void initQueue(struct Queue *q);
void push_back(struct Queue *q, int data);
int delNode(struct Queue *q);
int peek(struct Queue *q);
void clearQueue(struct Queue *q);