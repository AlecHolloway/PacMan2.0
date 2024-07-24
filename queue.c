#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

void initQ(struct queue *q) {
    q->head = NULL;
    q->tail = NULL;
}
//struct queue *enqueue(struct queue *q, int *location, int currentRow, int currentCol) {
//    struct node *newnode = (struct node*)malloc(sizeof(struct node)); 
//    if(newnode == NULL) { 
//        fprintf(stderr, "Memory allocation for newnode has failed");
//    }
//    if(q->head == NULL) {
//        q->head = newnode;
//        q->head->data = *location;
//        q->head->next = NULL; 
//        q->head->row = currentRow; 
//        q->head->column = currentCol;
//        q->tail = q->head;
//        return q;
//    }
//    else {
//        struct node* tmp = q->head;
//        while(tmp->next != NULL) {
//            tmp = tmp->next;
//        }
//        tmp->next = newnode;
//        tmp->next->data = *location;
//        tmp->next->next = NULL;
//        tmp->next->row = currentRow;
//        tmp->next->column = currentCol;
//        q->tail = tmp->next;
//        return q;
//    }
//
//}


struct queue *enqueue(struct queue *q, int *location) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node)); 
    if(newnode == NULL) { 
        fprintf(stderr, "Memory allocation for newnode has failed");
    }
    if(q->head == NULL) {
        q->head = newnode;
        q->head->data = *location;
        q->head->next = NULL; 
        q->tail = q->head;
        return q;
    }
    else {
        struct node* tmp = q->head;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newnode;
        tmp->next->data = *location;
        tmp->next->next = NULL;
        q->tail = tmp->next;
        return q;
    }

}

struct queue *dequeue(struct queue *q) {
    if(q->head == NULL) {
        fprintf(stderr, "Queue is already empty");
    }
    else {
        struct node *tmp;
        tmp = q->head->next;
        free(q->head);
        q->head = tmp;
    }
}


void displayQueue(struct queue *q) {
    if(q->head == NULL) {
        fprintf(stderr, "Queue is empty");
    }
    else {
        struct node *tmp;
        tmp = q->head;
        while(tmp != NULL) {
           printf("Data is %i\n", tmp->data);
           printf("Row is %i\n", tmp->row);
           printf("Column is %i\n", tmp->column);
           tmp = tmp->next;
        }
    }
} 





