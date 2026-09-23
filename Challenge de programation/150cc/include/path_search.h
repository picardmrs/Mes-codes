#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H

#include "map.h"
#include "physic.h"

/**
 * Structure représentant un nœud dans l'arbre de recherche A*.
 * Un nœud est un "état" atteint à un tour donné.
 */
typedef struct Node {
    int x, y;               /* Position sur la grille */
    int vx, vy;             /* Vitesse actuelle */
    int g;                  /* Coût réel (nombre de tours depuis le départ) */
    int f;                  /* Coût estimé (g + heuristique) */
    int ax, ay;             /* Accélération qui a mené à cet état (-1, 0 ou 1) */
    int fuel;               /* Carburant restant à cet état */
    struct Node *parent;    /* Pointeur vers le nœud précédent pour reconstruire le chemin */
} Node;

/**
 * Fonction principale appelée à chaque tour de jeu.
 * @param map La carte du circuit.
 * @param current L'état actuel de votre voiture (pos, vel, fuel).
 * @param h_map La carte des distances pré-calculée (Dijkstra inversé).
 * @return L'accélération (Vector2D) optimale à envoyer au GDC.
 */
Vector2D compute_next_move(const Map *map, CarState current, int *h_map,
                           Point adv1, Point adv2);

/**
 * Fonctions d'initialisation et de libération des structures
 */
void init_path_search_structures(const Map *map);
void free_path_search_structures(void);

/**
 * Fonctions de gestion du "Pool de Nœuds" (pour éviter les malloc en boucle)
 */
Node* get_new_node(int x, int y, int vx, int vy, int g, Node *parent, int ax, int ay);

/**
 * Gestion du marquage des états visités (Espace 4D : x, y, vx, vy)
 */
void reset_search(void);
void clear_visited(void);
int is_visited(int x, int y, int vx, int vy);
void mark_visited(int x, int y, int vx, int vy);
int is_visited_with_fuel(int x, int y, int vx, int vy, int fuel);
void mark_visited_with_fuel(int x, int y, int vx, int vy, int fuel);

#endif