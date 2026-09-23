#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "heap.h"

void initialize_distances_queue(const Map *map, int *dist, Heap *heap);
void update_neighbors(const Map *map, int *dist, Heap *heap, int x, int y);
int* dijkstra(const Map *map);

#endif
