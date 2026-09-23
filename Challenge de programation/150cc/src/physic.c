#include "physic.h"
#include "follow_line.h"
#include "map.h"

#include <math.h>

int is_move_valid(const Map *map, Point start, Point end, Point adv1, Point adv2) {
    InfoLine vline;
    Pos2Dint p;

    initLine(start.x, start.y, end.x, end.y, &vline);

    while (nextPoint(&vline, &p, +1) > 0) {
        
        if (p.x == start.x && p.y == start.y) {
            continue;
        }

        if (p.x < 0 || p.x >= map->width || p.y < 0 || p.y >= map->height) {
            return 0;
        }

        if (map->grid[p.y][p.x] == '.') {
            return 0;
        }

        if ((p.x == adv1.x && p.y == adv1.y) || (p.x == adv2.x && p.y == adv2.y)) {
            return 0;
        }
    }

    /* La boucle ne vérifie pas le point d'arrivée, on le fait manuellement */
    p.x = end.x;
    p.y = end.y;

    if (p.x < 0 || p.x >= map->width || p.y < 0 || p.y >= map->height) {
        return 0;
    }

    if (map->grid[p.y][p.x] == '.') {
        return 0;
    }

    if ((p.x == adv1.x && p.y == adv1.y) || (p.x == adv2.x && p.y == adv2.y)) {
        return 0;
    }

    return 1;
}

int is_cell_valid(const Map *map, int x, int y) {
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        return 0;
    }
    return map->grid[y][x] != '.';
}

int get_max_velocity_on_cell(const Map *map, int x, int y) {
    char cell;
    
    if (!is_cell_valid(map, x, y)) {
        return -1;
    }
    cell = map->grid[y][x];
    if (cell == '~') {
        return 1;
    }
    return 5;
}

int calculate_fuel_consumption(int dvx, int dvy, int vx, int vy, int on_sand) {
    int velocity_norm_sq;
    int drag;
    int consumption;
    
    velocity_norm_sq = vx * vx + vy * vy;
    drag = (int)(sqrt((double)velocity_norm_sq) * 3.0 / 2.0);
    
    consumption = dvx * dvx + dvy * dvy + drag;
    
    if (on_sand) {
        consumption += 1;
    }
    
    return -consumption;
}

int is_velocity_valid(int vx, int vy, int max_v) {
    int norm_sq;
    int max_v_sq;
    
    norm_sq = vx * vx + vy * vy;
    max_v_sq = max_v * max_v;
    return norm_sq <= max_v_sq;
}
