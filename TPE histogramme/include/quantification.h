#ifndef QUANTIFICATION_H
#define QUANTIFICATION_H

#include "histogramme.h"

/* Quantification par popularité avec grouping des couleurs bonus (R/2, G, B/4) */
int* quantification(histo h, int* tab, int K);

/* Mapping avec distance Manhattan (RGB) */
void mapping1(image input, image output, int* tab, int K);

/* Fonctions pour conversion RGB vers CIELAB */
double inverse_gamma(double valeur_normalisee);
double f(double t);
void rgb_to_lab(int R, int G, int B, double* L, double* a, double* b);

/* Mapping avec distance CIELAB (perception humaine) */
void mapping2(image input, image output, int* tab, int K);

/* Fonction pour quantifier les couleurs selon la règle bonus: R/2 = R'/2, G = G', B/4 = B'/4 */
void rgb_bonus(int R, int G, int B, int* qR, int* qG, int* qB);

/* Programme avec mapping1 (distance Manhattan RGB) */
void programme_quantification1(char* chemin_input, char* chemin_output, int K);

/* Programme avec mapping2 (distance CIELAB) */
void programme_quantification2(char* chemin_input, char* chemin_output, int K);

#endif
