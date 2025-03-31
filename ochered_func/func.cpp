#include"header_ochered.h"


void initQueue(struct Queue *q)
{
    q->head = q->end = NULL;
}


void push_back(struct Queue *q, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Ошибка: память не выделилась.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if(q->head == NULL)
    {
        q->head = q->end = newNode;
    }
    else
    {
        q->end->next = newNode;
        q->end = newNode;
    }
}

int delNode(struct Queue *q)
{
    if(q->head == NULL)
    {
        printf("Ошибка: очередь пустая.\n");
        return 0;
    }
    struct Node *temp = q->head;
    int val = q->head->data;

    q->head = q->head->next;
    if(q->head == NULL)
    {
        q->end = NULL;
    }
    free(temp);
    return val;
}

int peek(struct Queue *q)
{
    if(q->head == NULL)
    {
        printf("Ошибка: очередь пустая.\n");
        return 0;
    }
    return q->head->data;
}

void clearQueue(struct Queue *q)
{
    while(q->head != NULL)
    {
        delNode(q);
    }
}
