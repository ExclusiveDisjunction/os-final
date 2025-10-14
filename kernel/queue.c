#include "types.h"
#include "defs.h"
#include "queue.h"
#include "proc.h"

#define GROW_BY 5

void initializeQueue(Queue* q, int capacity, int quantum) {
    if (capacity <= 0) capacity = 5;
    if (capacity > MAX_QUEUE_SIZE) capacity = MAX_QUEUE_SIZE;
    if (quantum < 0) quantum = 0;

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    q->quantum = quantum;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

int isFull(Queue* q) {
    return q->size >= q->capacity;
}

void enqueue(Queue* q, struct proc* p) {
    if (isFull(q)) {
        // Cap the queue
        cprintf("Queue full, cannot enqueue pid %d\n", p ? p->pid : -1);
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->process_queue[q->rear] = p;
    q->size++;
}

struct proc* dequeue(Queue* q) {
    if (isEmpty(q)) {
        cprintf("Queue empty\n");
        return 0;
    }

    struct proc* p = q->process_queue[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cprintf("[Queue empty]\n");
        return;
    }

    cprintf("Queue (%d/%d): ", q->size, q->capacity);
    for (int i = 0; i < q->size; i++) {
        struct proc* p = q->process_queue[(q->front + i) % q->capacity];
        cprintf("P%d ", p ? p->pid : -1);
    }
    cprintf("\n");
}
