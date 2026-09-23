#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "physic.h"
#include "path_search.h"
#include "communication.h"
#include "dijkstra.h"

int main(void)
{
    Map *map;
    Point my_pos, adv1_pos, adv2_pos;
    Vector2D decision;
    int my_pilote_num;
    CarState current;
    int *h_map;
    int expected_x = -1, expected_y = -1;

    map = read_game_init();
    if (!map) {
        fprintf(stderr, "Erreur: impossible de lire la carte d'initialisation\n");
        fflush(stderr);
        return 1;
    }

    fprintf(stderr, "[MAP] Cartes lues. Start positions: 1=(%d,%d) 2=(%d,%d) 3=(%d,%d)\n",
            map->starts[0].x, map->starts[0].y,
            map->starts[1].x, map->starts[1].y,
            map->starts[2].x, map->starts[2].y);
    fflush(stderr);

    init_path_search_structures(map);
    
    h_map = dijkstra(map);

    my_pilote_num = -1;
    current.pos.x = 0;
    current.pos.y = 0;
    current.vel.x = 0;
    current.vel.y = 0;
    current.fuel = map->init_gas;

    while (read_game_turn(&my_pos, &adv1_pos, &adv2_pos) == 0) {
        
        fprintf(stderr, "[TURN] Me=(%d,%d) Adv1=(%d,%d) Adv2=(%d,%d)\n",
                my_pos.x, my_pos.y, adv1_pos.x, adv1_pos.y, adv2_pos.x, adv2_pos.y);
        fflush(stderr);

        if (my_pilote_num == -1) {
            char start_cell = map->grid[my_pos.y][my_pos.x];
            if (start_cell == '1') my_pilote_num = 1;
            else if (start_cell == '2') my_pilote_num = 2;
            else if (start_cell == '3') my_pilote_num = 3;
            else {
                fprintf(stderr, "[WARN] Position (%d,%d) ne correspond à aucun départ (cellule '%c')\n", my_pos.x, my_pos.y, start_cell);
                fflush(stderr);
                my_pilote_num = 1;
            }
            fprintf(stderr, "[IDENTITY] Nous sommes le pilote %d\n", my_pilote_num);
            fflush(stderr);
        }

        if (expected_x != -1 && (my_pos.x != expected_x || my_pos.y != expected_y)) {
            fprintf(stderr, "[WARN] Collision ou reset detecte! Vitesse remise a 0.\n");
            fflush(stderr);
            current.vel.x = 0;
            current.vel.y = 0;
        }

        current.pos.x = my_pos.x;
        current.pos.y = my_pos.y;

        decision = compute_next_move(map, current, h_map, adv1_pos, adv2_pos);

        fprintf(stderr, "[A*] Accélération: dvx=%d dvy=%d\n", decision.x, decision.y);
        fflush(stderr);

        send_acceleration(decision);

        current.vel.x += decision.x;
        current.vel.y += decision.y;
        current.fuel += calculate_fuel_consumption(decision.x, decision.y, current.vel.x - decision.x, current.vel.y - decision.y, map->grid[my_pos.y][my_pos.x] == '~');
        expected_x = my_pos.x + current.vel.x;
        expected_y = my_pos.y + current.vel.y;
    }

    fprintf(stderr, "[END] Fin de la simulation\n");
    fflush(stderr);

    free_path_search_structures();
    free(h_map);
    free_map(map);

    return 0;
}