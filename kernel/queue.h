#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "types.h"
#include "param.h"

struct proc;

#define MAX_QUEUE_SIZE NPROC

typedef struct {
    struct proc* process_queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
    int capacity;
    int quantum;
} Queue;

// Kernel-safe prototypes (no malloc/free)
void initializeQueue(Queue* q, int capacity, int quantum);
int isEmpty(Queue* q);
int isFull(Queue* q);
void enqueue(Queue* q, struct proc* p);
struct proc* dequeue(Queue* q);
void printQueue(Queue* q);

#endif
