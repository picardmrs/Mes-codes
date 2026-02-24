#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#ifndef __TRANSFORMATIONS__
#define __TRANSFORMATIONS__


/* Elimine les pixels inférieurs à une certaine valeur. */
extern void seuillage(int val, char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit);

/* Norme déterminer à partir du gradient suivant les axes x et y. */
extern void gradient( char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit);

/* Permet de réduire le bruit dans une image.*/
extern void lissage( char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit);

#endif