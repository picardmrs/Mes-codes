#ifndef PHYSIC_H
#define PHYSIC_H

#include "map.h"
#include <math.h>

/* Basic 2D vector types */
typedef struct {
    int x;
    int y;
} Vector2D;

/* Car state: position, velocity, fuel */
typedef struct {
    Point pos;
    Vector2D vel;
    int fuel;
} CarState;

/**
 * Validates if a move is physically possible.
 * Checks:
 * - End position in bounds
 * - End position not off-track ('.')
 * - Trajectory doesn't cross off-track cells
 * 
 * @param map The map
 * @param start Starting position
 * @param end Ending position
 * @return true if move is valid, false otherwise
 */
int is_move_valid(const Map *map, Point start, Point end, Point adv1, Point adv2);

/**
 * Checks if a cell can be traversed (not off-track).
 * 
 * @param map The map
 * @param x X coordinate
 * @param y Y coordinate
 * @return true if cell is traversable, false if off-track
 */
int is_cell_valid(const Map *map, int x, int y);

/**
 * Calculates the maximum velocity allowed on a cell.
 * 
 * @param map The map
 * @param x X coordinate
 * @param y Y coordinate
 * @return Maximum speed: 5 for normal/finish, 1 for sand, -1 for invalid
 */
int get_max_velocity_on_cell(const Map *map, int x, int y);

/**
 * Calculates fuel consumption for an acceleration.
 * Formula: Δc = -( dvx² + dvy² + floor( sqrt( 3*(vx²+vy²) / 2 ) ) )
 * Extra -1 on sand.
 * 
 * @param dvx Acceleration X (-1, 0, or 1)
 * @param dvy Acceleration Y (-1, 0, or 1)
 * @param vx Current velocity X
 * @param vy Current velocity Y
 * @param on_sand 1 if on sand, 0 otherwise
 * @return Fuel consumption (negative value to subtract from fuel)
 */
int calculate_fuel_consumption(int dvx, int dvy, int vx, int vy, int on_sand);

/**
 * Checks if velocity norm is within limits.
 * 
 * @param vx Velocity X
 * @param vy Velocity Y
 * @param max_v Maximum allowed velocity norm
 * @return 1 if within limits, 0 otherwise
 */
int is_velocity_valid(int vx, int vy, int max_v);

#endif
