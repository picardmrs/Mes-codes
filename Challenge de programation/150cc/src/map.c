#include "map.h"

Map* read_map(void) {
    int w, h, g, i, j, c;
    Map *map;
    Point p;

    if (scanf("%d %d %d", &w, &h, &g) != 3) {
        return NULL;
    }

    map = (Map *)malloc(sizeof(Map));
    map->width = w;
    map->height = h;
    map->init_gas = g;
    map->nb_starts = 0;
    map->nb_finish = 0;

    map->grid = (char **)malloc(h * sizeof(char *));
    map->starts = (Point *)malloc(3 * sizeof(Point));
    map->finish_line = (Point *)malloc(w * h * sizeof(Point));

    /* pour arriver à la premiere case du circuit */
    while ((c = getchar()) != '\n' && c != EOF);

    for (i = 0; i < h; i++) {
        map->grid[i] = (char *)malloc((w + 1) * sizeof(char));
        for (j = 0; j < w; j++) {
            char cell = getchar();
            map->grid[i][j] = cell;

            if (cell == '1' || cell == '2' || cell == '3') {
                p.x = j;
                p.y = i;
                map->starts[map->nb_starts++] = p;
            } else if (cell == '=') {
                p.x = j;
                p.y = i;
                map->finish_line[map->nb_finish++] = p;
            }
        }
        getchar();
    }

    return map;
}

void free_map(Map *map) {
    int i;

    if (!map)
        return;
    for (i = 0; i < map->height; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
    free(map->starts);
    free(map->finish_line);
    free(map);
}

int is_in_bounds(const Map *map, int x, int y) {
    return (x >= 0 && x < map->width && y >= 0 && y < map->height);
}
