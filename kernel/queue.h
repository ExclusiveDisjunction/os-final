#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct proc;

typedef struct {
    struct proc** process_queue;  // dynamic array of pointers
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* initializeQueue(int capacity);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, struct proc* process);
struct proc* dequeue(Queue* q);
void printQueue(Queue* q);
void freeQueue(Queue* q);

#endif // _QUEUE_H_
