#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int width;
    int height;
    char **grid;

    Point *starts;
    int nb_starts;
    Point *finish_line;
    int nb_finish;
    int init_gas;
} Map;

Map* read_map();

void free_map(Map *map);

/* Fonction utilitaire pour vérifier si une coordonnee est dans la map */
int is_in_bounds(const Map *map, int x, int y);

#endif