// queue.h
#include "consts.h"
#ifndef QUEUE_H 
#define QUEUE_H
struct node {
    int data;
    int row;
    int column;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
};

void initQ(struct queue *);
//struct queue *enqueue(struct queue *q, int *location, int currentRow, int currentCol);
struct queue *enqueue(struct queue *q, int *location);
struct queue *dequeue(struct queue *);
void displayQueue(struct queue *);
#endif
