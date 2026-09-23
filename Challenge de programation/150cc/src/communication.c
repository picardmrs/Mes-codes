#include "communication.h"
#include "map.h"
#include "physic.h"
#include <stdio.h>
#include <string.h>

Map* read_game_init() {
    return read_map();
}

int read_game_turn(Point *my_pos, Point *adv1_pos, Point *adv2_pos) {
    if (!my_pos || !adv1_pos || !adv2_pos) {
        return -1;
    }
    
    if (scanf("%d %d %d %d %d %d", 
              &my_pos->x, &my_pos->y,
              &adv1_pos->x, &adv1_pos->y,
              &adv2_pos->x, &adv2_pos->y) != 6) {
        return -1;
    }
    
    return 0;
}

int send_acceleration(Vector2D accel) {
    if (printf("%d %d\n", accel.x, accel.y) < 0) {
        return -1;
    }
    fflush(stdout);
    return 0;
}
