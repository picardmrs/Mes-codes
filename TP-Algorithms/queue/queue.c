#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../list/list.h"

/**
 * @brief Creates a new, empty queue.
 *
 * @return A pointer to the newly created queue.
 */
 Queue* createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL; 
    return queue;
}


/**
 * @brief Checks whether the queue is empty.
 *
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue q) {
    if(q.front == NULL){
        return 1;
    }
    return 0;
}


/**
 * @brief Prints all the elements in the queue, from front to rear.
 *
 * @param q The queue to print.
 */
void queuePrint(Queue q) {
    Cell *current= q.front; 

    while(current != NULL){
        printf("%d\n", current->value);
        current = current->nextCell;
    }

    return;
}


/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q A pointer to the queue to add the element to.
 * @param data The data to be added to the queue.
 */
void enqueue(Queue* q, int data) {
    Cell *cell = malloc(sizeof(Cell));
    cell->value = data; 
    cell->nextCell = NULL; 

    if(q->front == NULL){
        q->front = cell;
        q->rear = cell;
    }
    else{
        q->rear->nextCell = cell;
        q->rear = cell; 
    }
    return;
}

/**
 * @brief Removes and returns the front element of the queue.
 *
 * @param q A pointer to the queue to remove the front element from.
 * @return The value stored in the front element of the queue.
 */
int dequeue(Queue* q) {
    int value;

    value = q->front->value;
    q->front = q->front->nextCell;     

    return value;
}


/**
 * @brief Returns the value of the front node but doesn't modify the queue
 *
 * @param q The queue to get the front value.
 * @return The value of the front node.
 */
int queueGetFrontValue(Queue q) {

    return q.front->value;
}
