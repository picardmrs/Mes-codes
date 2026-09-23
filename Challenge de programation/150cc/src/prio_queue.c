#include "prio_queue.h"
#include "path_search.h"
#include <stdlib.h>
#include <stdio.h>

static void pq_swap(PrioQueueNode *a, PrioQueueNode *b)
{
    PrioQueueNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void pq_sift_up(PrioQueue *q, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (q->data[index].priority >= q->data[parent].priority) {
            return;
        }
        pq_swap(&q->data[index], &q->data[parent]);
        index = parent;
    }
}

static void pq_sift_down(PrioQueue *q, int index)
{
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < q->size && q->data[left].priority < q->data[smallest].priority) {
            smallest = left;
        }
        if (right < q->size && q->data[right].priority < q->data[smallest].priority) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        pq_swap(&q->data[index], &q->data[smallest]);
        index = smallest;
    }
}

void pq_init(PrioQueue *q, int capacity)
{
    q->data = malloc(sizeof(PrioQueueNode) * capacity);
    if (q->data == NULL) {
        fprintf(stderr, "Failed to allocate priority queue\n");
        q->capacity = 0;
        q->size = 0;
        return;
    }
    q->capacity = capacity;
    q->size = 0;
}

void pq_free(PrioQueue *q)
{
    free(q->data);
    q->data = NULL;
    q->size = 0;
    q->capacity = 0;
}

bool pq_is_empty(const PrioQueue *q)
{
    return q->size == 0;
}

void pq_push(PrioQueue *q, struct Node *node, int priority)
{
    if (q->size >= q->capacity) {
        int new_capacity = q->capacity > 0 ? q->capacity * 2 : 8;
        PrioQueueNode *new_data = realloc(q->data, sizeof(PrioQueueNode) * new_capacity);
        if (new_data == NULL) {
            fprintf(stderr, "Failed to resize priority queue\n");
            return;
        }
        q->data = new_data;
        q->capacity = new_capacity;
    }
    q->data[q->size].node = node;
    q->data[q->size].priority = priority;
    pq_sift_up(q, q->size);
    q->size += 1;
}

PrioQueueNode pq_pop(PrioQueue *q)
{
    PrioQueueNode result;
    result.node = NULL;
    result.priority = 0;
    
    if (q->size == 0) {
        return result;
    }
    result = q->data[0];
    q->data[0] = q->data[q->size - 1];
    q->size -= 1;
    pq_sift_down(q, 0);
    return result;
}
