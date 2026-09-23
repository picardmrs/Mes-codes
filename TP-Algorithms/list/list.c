/**
 * @file list.c
 * @brief Implementation file for a linked list
 *
 * This file contains the implementation of the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List newList() {
    return NULL;
}

void freeList(List L) {
    List current = L;
    List next;
    while (current != NULL) {
        next = current->nextCell;
        free(current->key);
        free(current);
        current = next;
    }
}

void printList(List L, int type) {
    List current = L->nextCell;
    int first = 1;

    printf("[");
    while (current != L) {
        if (!first) {
            printf(",");
        }
        if (type == 0) {
            printf("%d", current->value);

        }
        else {
            printf("(%s, %d)", current->key, current->value);
        }
        first = 0;
        current = current->nextCell;
    }
    printf("]\n");
    return;
}

Cell* findKeyInList(List L, string key) {
    List current = L;
    while (current != NULL) {
        if (key == NULL && current->key == NULL)
            return current;
        if (key != NULL && current->key != NULL && strcmp(current->key, key) == 0)
            return current;
        current = current->nextCell;
    }
    return NULL;
}

List delKeyInList(List L, string key) {
    List previous = NULL;
    List current = L;

    while (current != NULL) {
        int match = (key == NULL && current->key == NULL) ||
                    (key != NULL && current->key != NULL && strcmp(current->key, key) == 0);
        if (match) {
            if (previous == NULL)
                L = current->nextCell;
            else
                previous->nextCell = current->nextCell;
            free(current->key);
            free(current);
            return L;
        }
        previous = current;
        current = current->nextCell;
    }
    return L;
}

List addKeyValueInList(List L, string key, int value) {
    List newCell = malloc(sizeof(Cell));
    newCell->key = (key == NULL) ? NULL : strdup(key);
    newCell->value = value;
    newCell->nextCell = L;
    return newCell;
}
