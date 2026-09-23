#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "map.h"
#include "physic.h"

/**
 * Lit l'initialisation de la partie (largeur, hauteur, fuel, puis la carte)
 */
Map* read_game_init(void);

/**
 * Lit les positions du tour courant.
 * Renvoie 0 si succès, -1 si fin de fichier ou erreur.
 */
int read_game_turn(Point *my_pos, Point *adv1_pos, Point *adv2_pos);

/**
 * Envoie la décision d'accélération au GDC (Gestionnaire De Course).
 */
int send_acceleration(Vector2D accel);

#endif