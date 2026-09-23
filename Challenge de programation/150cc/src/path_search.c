#include "path_search.h"
#include "prio_queue.h"
#include "physic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static Node *node_pool = NULL;
static int pool_ptr = 0;
static int max_nodes = 0;

typedef struct {
    int search_id;
    int fuel;
} StateInfo;
static StateInfo *visited = NULL;
static int current_search_id = 0;
static int map_w = 0;
static int map_h = 0;
static int total_visited_size = 0;

#define V_SIZE 11
#define V_OFFSET 5


void init_path_search_structures(const Map *map){
    map_w = map->width;
    map_h = map->height;

    total_visited_size = map_w * map_h * V_SIZE * V_SIZE;
    max_nodes = map_w * map_h * V_SIZE * V_SIZE;
    
    if (max_nodes > 500000) {
        max_nodes = 500000;
    }
    node_pool = (Node *)malloc(max_nodes * sizeof(Node));

    visited = (StateInfo *)calloc(total_visited_size, sizeof(StateInfo));
    current_search_id = 0;
}

void free_path_search_structures(void){
    if (node_pool) {
        free(node_pool);
        node_pool = NULL;
    }
    if (visited) {
        free(visited);
        visited = NULL;
    }
}



void reset_search(void){
    int visited_size;
    
    pool_ptr = 0;
    if (visited){
        current_search_id++;
        if (current_search_id <= 0) {
            visited_size = map_w * map_h * V_SIZE * V_SIZE;
            memset(visited, 0, visited_size * sizeof(StateInfo));
            current_search_id = 1;
        }
    }
}

int is_state_better_or_equal(int x, int y, int vx, int vy, int current_fuel){
    int vxi;
    int vyi;
    int index;
    
    if (x < 0 || x>= map_w || y < 0 || y >= map_h) {
        return 1;
    }
    vxi = vx + V_OFFSET;
    vyi = vy + V_OFFSET;
    if (vxi < 0 || vxi >= V_SIZE || vyi<0 || vyi >= V_SIZE){
        return 1;
    }

    index =(((y * map_w + x)* V_SIZE + vxi) *V_SIZE) +vyi;
    if (visited[index].search_id == current_search_id){
        return visited[index].fuel >= current_fuel;
    }
    return 0;
}

void mark_state_visited(int x, int y, int vx, int vy, int fuel){
    int vxi;
    int vyi;
    int index;
    
    if (x < 0 || x >= map_w || y < 0 || y>= map_h){
        return;
    }
    
    vxi = vx + V_OFFSET;
    vyi = vy + V_OFFSET;
    if (vxi < 0 || vxi >= V_SIZE || vyi < 0 || vyi >= V_SIZE){
        return;
    }
    
    index = (((y * map_w + x)* V_SIZE + vxi)* V_SIZE) + vyi;
    visited[index].search_id = current_search_id;
    visited[index].fuel = fuel;
}

Node* get_new_node(int x, int y, int vx, int vy, int g, Node *parent, int ax, int ay){
    Node *n;
    
    if (pool_ptr >= max_nodes){
        return NULL;
    }
    n = &node_pool[pool_ptr++];
    n->x = x;
    n->y = y;
    n->vx = vx;
    n->vy = vy;
    n->g= g;
    n->parent =parent;
    n->ax = ax;
    n->ay = ay;
    n->fuel =0;
    n->f = 0;
    return n;
}


static void process_node_neighbors(const Map *map, Node *curr, int *h_map,Point adv1, Point adv2, PrioQueue *open_list,Node **best_node, int *best_h){
    int ax, ay;
    int n_vx, n_vy, n_x, n_y;
    int max_v, fuel_cost, new_fuel, on_sand;
    Point p1,p2;
    Node *child;

    for (ax = -1; ax <= 1; ax++) {
        for (ay = -1; ay <= 1; ay++) {
            n_vx = curr->vx + ax;
            n_vy = curr->vy + ay;
            
            max_v = get_max_velocity_on_cell(map, curr->x, curr->y);
            if (max_v == -1 || !is_velocity_valid(n_vx, n_vy, max_v)) {
                continue;
            }
            
            n_x = curr->x + n_vx;
            n_y = curr->y + n_vy;

            p1.x = curr->x;
            p1.y = curr->y;
            p2.x = n_x;
            p2.y = n_y;
            if (!is_move_valid(map, p1, p2, adv1, adv2)) {
                continue;
            }

            on_sand = (map->grid[curr->y][curr->x] == '~');
            fuel_cost = calculate_fuel_consumption(ax, ay, curr->vx, curr->vy, on_sand);
            new_fuel = curr->fuel + fuel_cost;
            if (new_fuel <= 0) {
                continue;
            }

            if (!is_state_better_or_equal(n_x, n_y,n_vx, n_vy, new_fuel)){
                mark_state_visited(n_x, n_y,n_vx, n_vy, new_fuel);
                child = get_new_node(n_x, n_y,n_vx, n_vy, curr->g +1, curr, ax, ay);
                if (child) {
                    child->fuel = new_fuel;
                    
                    if (h_map) child->f = child->g *7 + h_map[n_y * map_w + n_x];
                    else child->f = child->g * 7;
                    
                    pq_push(open_list, child, child->f);
                    
                    if (h_map && h_map[n_y * map_w + n_x] < *best_h) {
                        *best_node = child;
                        *best_h = h_map[n_y * map_w + n_x];
                    }
                }
            }
        }
    }
}

static Vector2D reconstruct_first_move(Node *best_node, Node *start){
    Vector2D decision;
    Node *move_node = best_node;

    if (move_node != start && move_node != NULL){
        while (move_node->parent != NULL && move_node->parent->parent != NULL){
            move_node = move_node->parent;
        }
        decision.x = move_node->ax;
        decision.y = move_node->ay;
    } else{
        decision.x = 0;
        decision.y = 0;
    }
    return decision;
}


Vector2D compute_next_move(const Map *map, CarState current, int *h_map,
                           Point adv1, Point adv2) {
    PrioQueue open_list;
    Node *start;
    Node *curr;
    Node *best_node;
    int best_h;
    Vector2D error;
    Vector2D decision;
    PrioQueueNode pqn;
    clock_t search_start;

    reset_search();
    
    pq_init(&open_list, max_nodes);
    if (open_list.capacity == 0) {
        fprintf(stderr, "Failed to initialize priority queue\n");
        error.x = 0;
        error.y = 0;
        return error;
    }
    
    start = get_new_node(current.pos.x, current.pos.y, 
                         current.vel.x, current.vel.y, 
                         0, NULL, 0, 0);
    if (!start) {
        pq_free(&open_list);
        fprintf(stderr, "Failed to allocate start node\n");
        error.x = 0;
        error.y = 0;
        return error;
    }
    
    start->fuel = current.fuel;
    
    if (h_map){
        start->f = start->g * 7 + h_map[start->y * map_w + start->x];
    } 
    else{
        start->f = start->g * 7;
    }
    
    mark_state_visited(start->x, start->y, start->vx, start->vy, start->fuel);
    pq_push(&open_list, start, start->f);

    best_node = start;
    best_h = 1000000; 

    search_start = clock();

    while (!pq_is_empty(&open_list) &&
           ((double)(clock() - search_start) / CLOCKS_PER_SEC) < 0.9){
        pqn = pq_pop(&open_list);
        curr = pqn.node;

        if (!curr) break;

        if (map->grid[curr->y][curr->x] == '=') {
            best_node = curr;
            break;
        }

        process_node_neighbors(map, curr, h_map, adv1, adv2, &open_list, &best_node, &best_h);
    }

    decision = reconstruct_first_move(best_node, start);

    pq_free(&open_list);
    reset_search();
    
    return decision;
}

void clear_visited(void){
    int visited_size;
    if (visited) {
        visited_size = map_w * map_h*V_SIZE * V_SIZE;
        memset(visited, 0, visited_size * sizeof(StateInfo));
        current_search_id = 0;
    }
}

int is_visited_with_fuel(int x,int y, int vx, int vy, int fuel){
    return is_state_better_or_equal(x, y, vx,vy, fuel);
}

void mark_visited_with_fuel(int x,int y, int vx, int vy, int fuel){
    mark_state_visited(x, y, vx,vy, fuel);
}
