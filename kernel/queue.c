#include "queue.h"
#include "param.h"
#include "proc.h"   // assuming struct proc is defined there

#define GROW_BY 5
// Set the max queue size equal to the max number of processes that can spawn
#define MAX_QUEUE_SIZE NPROC 

Queue* initializeQueue(int capacity) {
    if (capacity <= 0) capacity = 5;
    if (capacity > MAX_QUEUE_SIZE) capacity = MAX_QUEUE_SIZE;

    Queue* q = malloc(sizeof(Queue));
    if (!q) {
        fprintf(stderr, "Failed to allocate Queue struct\n");
        return NULL;
    }

    q->process_queue = malloc(capacity * sizeof(struct proc*));
    if (!q->process_queue) {
        fprintf(stderr, "Failed to allocate queue array\n");
        free(q);
        return NULL;
    }

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;

    return q;
}

bool isEmpty(Queue* q) {
    return q->size == 0;
}

bool isFull(Queue* q) {
    return q->size == q->capacity;
}

static void growQueue(Queue* q) {
    if (q->capacity >= MAX_QUEUE_SIZE) {
        printf("Queue reached maximum size limit (%d)\n", MAX_QUEUE_SIZE);
        return;
    }

    int new_capacity = q->capacity + GROW_BY;
    if (new_capacity > MAX_QUEUE_SIZE) new_capacity = MAX_QUEUE_SIZE;

    struct proc** new_array = malloc(new_capacity * sizeof(struct proc*));
    if (!new_array) {
        fprintf(stderr, "Failed to grow queue\n");
        return;
    }

    // Copy elements from old circular buffer to new linear buffer
    for (int i = 0; i < q->size; i++) {
        new_array[i] = q->process_queue[(q->front + i) % q->capacity];
    }

    free(q->process_queue);
    q->process_queue = new_array;
    q->capacity = new_capacity;
    q->front = 0;
    q->rear = q->size - 1;

    printf("Queue capacity increased to %d\n", q->capacity);
}

void enqueue(Queue* q, struct proc* process) {
    if (isFull(q)) {
        growQueue(q);
        if (isFull(q)) { // grow failed or hit max
            printf("Queue is full! Cannot enqueue process.\n");
            return;
        }
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->process_queue[q->rear] = process;
    q->size++;
}

struct proc* dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return NULL;
    }

    struct proc* p = q->process_queue[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("[Queue empty]\n");
        return;
    }

    printf("Queue (%d/%d): ", q->size, q->capacity);
    for (int i = 0; i < q->size; i++) {
        struct proc* p = q->process_queue[(q->front + i) % q->capacity];
        printf("P%d ", p ? p->pid : -1);  // assumes struct proc has a pid field
    }
    printf("\n");
}

void freeQueue(Queue* q) {
    if (!q) return;
    free(q->process_queue);
    free(q);
}
