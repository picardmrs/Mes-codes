#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define N 256  /* Nombre de niveaux de couleur (0-255) */

#include "bool.h"
#include "image.h"

/* Typedefs (structures définies dans .c) */

typedef struct cell *cell;  /* Liste chaînée pour les valeurs de B et leurs fréquences */
typedef struct pixel *pixel;  /* Structure pour un pixel RGB */
typedef cell **histo;  /* Histogramme 2D (tableau de listes chaînées) */
typedef struct histo_iter *histo_iter;  /* Itérateur pour parcourir un histogramme */


/* Déclarations des fonctions */

/* Partie 2.1 */
cell create_cell(int B, cell next);
cell insert_cell(cell head, int B);
cell delete_list(cell list);

/* Partie 2.2 */
histo create_histo(void);
void init_histo(histo h, image img);
void delete_histo(histo h);

/* Partie 2.3 */
int give_freq_histo(histo h,int R,int G,int B);
histo_iter create_histo_iter(histo h);
void start_histo_iter(histo_iter iter, histo h);
boolean next_histo_iter(histo_iter iter, histo h);
void give_color_histo_iter(histo_iter iter,int* couleur);
int give_freq_histo_iter(histo_iter iter);
void delete_histo_iter(histo_iter iter);
void delete_histo_iter(histo_iter iter);
int give_freq_histo_iter(histo_iter iter);

/* Implémentation pphmhsit */
void histo_display(char* chemin_image);

#endif
