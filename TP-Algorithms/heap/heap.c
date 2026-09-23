#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * @brief Helper function to swap two elements in the heap.
 * @param h A pointer to the Heap data structure.
 * @param i The index of the first element.
 * @param j The index of the second element.
 */
void swap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}


/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {
    if (n <= 0 ){
        return NULL;
    }
    Heap *h = malloc(sizeof(Heap));

    h->n = n;
    h -> nbElements = 0;
    h->position = malloc(n * sizeof(int));
    h->heap = malloc(n * sizeof(int));
    h->priority = malloc(n * sizeof(double));
    for( int i = 0; i <n ; i++){
        h->position[i] = -1;
        h->priority[i] = -1;
    }
    return h;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap h) {
    printf("Heap: ");
    printf("n: %d \nnbElements: %d\n", h.n, h.nbElements);
    printf("Position: [");
    for(int i = 0 ; i < h.n ; i++){
        printf("%d, ", h.position[i]);
    }
    printf("]\n");
    printf("Priority: [");
    for(int i = 0 ; i < h.n ; i++){
        printf("%lf, ", h.priority[i]);
    }
    printf("]\n");
    printf("Heap: [");
    for(int i = 0 ; i < h.n ; i++){
        printf("%d, ", h.heap[i]);
    }
    printf("]\n");
    return;
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority.
 */
int getElement(Heap h) {
    if (h.nbElements == 0) return -1;
    return h.heap[0];
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority) {
    int i;
    int intermediaire;
    
    if (h->nbElements == h->n){
        printf("Heap est plein");
        return;
    }
    h->heap[h->nbElements] = element;
    h->priority[element] = priority;
    h->position[element] = h->nbElements;
    h->nbElements++;
    i = h->nbElements - 1;
    while (i>0){
        if (h->priority[h->heap[i]] < h->priority[h->heap[(i-1)/2]]){
            intermediaire = h->heap[i];
            h->heap[i] = h->heap[(i-1)/2];
            h->heap[(i-1)/2] = intermediaire;
            h->position[h->heap[i]] = i;
            h->position[h->heap[(i-1)/2]] = (i-1)/2;
            i = (i-1)/2;
        } else {
            break;
        }
    }
    return;
}

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority) {
        if (h->position[element] == -1){
            printf("Element n'existe pas dans le heap");
            return;
        }
        h->priority[element] = priority;
        int i = h->position[element];
        
        while (i > 0) {
            if (h->priority[h->heap[i]] < h->priority[h->heap[(i-1)/2]]) {
                swap(h, i, (i-1)/2);
                i = (i-1)/2;
            } else {
                break;
            }
        }
                i = h->position[element];
        while (2*i + 1 < h->nbElements) {
            int leftChild = 2*i + 1;
            int rightChild = 2*i + 2;
            int smallest = leftChild;
            
            if (rightChild < h->nbElements && h->priority[h->heap[rightChild]] < h->priority[h->heap[leftChild]]) {
                smallest = rightChild;
            }
            
            if (h->priority[h->heap[smallest]] < h->priority[h->heap[i]]) {
                swap(h, i, smallest);
                i = smallest;
            } else {
                break;
            }
        }
    return;
}


/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
    int removed = h->heap[0];
    h->position[removed] = -1;
    h->nbElements--;
    
    h->heap[0] = h->heap[h->nbElements];
    h->position[h->heap[0]] = 0;
    
    int i = 0;
    while (2*i + 1 < h->nbElements) {
        int leftChild = 2*i + 1;
        int rightChild = 2*i + 2;
        int smallest = leftChild;
        
        if (rightChild < h->nbElements && h->priority[h->heap[rightChild]] < h->priority[h->heap[leftChild]]) {
            smallest = rightChild;
        }
        
        if (h->priority[h->heap[smallest]] < h->priority[h->heap[i]]) {
            swap(h, i, smallest);
            i = smallest;
        } else {
            break;
        }
    }
    
    return removed;
}


