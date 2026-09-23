#ifndef PRIO_QUEUE_H
#define PRIO_QUEUE_H

#include <stdbool.h>

/* Forward declaration to avoid circular dependency */
struct Node;

typedef struct {
    struct Node *node;     /* Pointer to Node */
    int priority;
} PrioQueueNode;

typedef struct {
    PrioQueueNode *data;
    int size;
    int capacity;
} PrioQueue;

void pq_init(PrioQueue *q, int capacity);
void pq_free(PrioQueue *q);
bool pq_is_empty(const PrioQueue *q);
void pq_push(PrioQueue *q, struct Node *node, int priority);
PrioQueueNode pq_pop(PrioQueue *q);

#endif /* PRIO_QUEUE_H */
