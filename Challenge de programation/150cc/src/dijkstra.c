#include "dijkstra.h"

void initialize_distances_queue(const Map *map, int* dist, Heap *heap){
    int i,j,x,y;

    for(i = 0; i < map->height; i++){
        for(j = 0 ; j < map->width ; j++){
            dist[i* map->width + j] = -1;
        }
    }
    for (i = 0; i < map->nb_finish; i++) {
        x = map->finish_line[i].x;
        y = map->finish_line[i].y;
        dist[y * map->width + x] = 0;
        insertHeap(heap, y * map->width + x, 0);
    }
}

void update_neighbors(const Map *map, int* dist, Heap *heap, int x, int y){
    int k;
    int width = map->width;
    int current_cost = dist[y * width + x];
    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    int nx;
    int ny;
    int new_cost;
    char cell;

    for (k = 0; k < 8; k++) {
        nx = x + dx[k];
        ny = y + dy[k];

        if (!is_in_bounds(map, nx, ny)) {
            continue;
        }

        cell = map->grid[ny][nx];
        if (cell == '.') {
            continue;
        }

        new_cost = current_cost + ((cell == '~') ? 7 : 1);

        if (dist[ny * width + nx] == -1 || new_cost < dist[ny * width + nx]) {
            dist[ny * width + nx] = new_cost;
            insertHeap(heap, ny * width + nx, new_cost);
        }
    }
}

int* dijkstra(const Map *map){
    int* dist = malloc(map->height * map->width * sizeof(int));
    Heap *heap = createHeap(map->width * map->height);
    int x,y;
    int element;
     int popped_cost;

    initialize_distances_queue(map, dist, heap);

    while(heap->nbElements > 0){
        popped_cost = heap->priority[getElement(*heap)];
        element = removeElement(heap);
        x = element % map->width;
        y = element / map->width;

        if (dist[element] < popped_cost) continue;

        update_neighbors(map, dist, heap, x, y);
    }

    freeHeap(heap);

    return dist;
}

