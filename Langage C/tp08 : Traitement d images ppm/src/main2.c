#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformations.h"

#define MAX_CHAR 50

int main(){

    char choix[MAX_CHAR];
    char img_entree[MAX_CHAR];
    char img_sortie[MAX_CHAR];
    int sup_gauche[2] = {-1, -1};
    int inf_droit[2] = {-1, -1};

    while(scanf("%s", choix) == 1){

        if(strcmp("quit", choix) == 0){
            break;
        }
        else if(strcmp("seuillage", choix) == 0){
            int val;
            scanf("%d %s %s %d %d %d %d", &val, img_entree, img_sortie, &sup_gauche[0], &sup_gauche[1], &inf_droit[0], &inf_droit[1]);
            seuillage(val, img_entree, img_sortie, sup_gauche, inf_droit);
            sup_gauche[0] = sup_gauche[1] = inf_droit[0] = inf_droit[1] = -1;
        }
        else if(strcmp("gradient", choix) == 0){
            scanf("%s %s %d %d %d %d", img_entree, img_sortie, &sup_gauche[0], &sup_gauche[1], &inf_droit[0], &inf_droit[1]);
            gradient( img_entree, img_sortie, sup_gauche, inf_droit);
            sup_gauche[0] = sup_gauche[1] = inf_droit[0] = inf_droit[1] = -1;


        }else if(strcmp("lissage", choix) == 0){
            scanf("%s %s %d %d %d %d", img_entree, img_sortie, &sup_gauche[0], &sup_gauche[1], &inf_droit[0], &inf_droit[1]);
            lissage( img_entree, img_sortie, sup_gauche, inf_droit);
            sup_gauche[0] = sup_gauche[1] = inf_droit[0] = inf_droit[1] = -1;

        }
    }
    
    return 0;
}