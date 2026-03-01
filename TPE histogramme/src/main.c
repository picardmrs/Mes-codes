#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "histogramme.h"
#include "image.h"
#include "quantification.h"

void menu_display(char * menu[]){
    int i = 1;
    printf("%s", menu[0]);
    while(menu[i] != NULL){
        printf("%d. %s\n", i, menu[i]);
        i++;
    }
}

int main(void) {
    int choix;
    char chemin_image[50];
    int K;
    char chemin_sortie[50];

    char* menu[] = {
        "====== Menu Histogramme ======\n",
        "Afficher l'histogramme complet (R,G,B,luminosité,fréquence)",
        "Quantification avec mapping1 (distance Manhattan RGB)",
        "Quantification avec mapping2 (distance CIELAB)",
        "Quitter\n",
        NULL
    };

    do {
        menu_display(menu);
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("Nom exacte de l'image (elle doit être dans ./ressources/image/): ");
                scanf("%s", chemin_image );

                histo_display(chemin_image);
                break;

            case 2: {
                char chemin_complet[200];
                char chemin_sortie_complet[250];
                printf("Nom exacte de l'image (elle doit être dans ./ressources/IMAGES/): ");
                scanf("%s", chemin_image);
                
                printf("Nombre de couleurs K : ");
                scanf("%d", &K);
                
                printf("Nom du fichier de sortie : ");
                scanf("%s", chemin_sortie);
                
                sprintf(chemin_complet, "./ressources/IMAGES/%s", chemin_image);
                sprintf(chemin_sortie_complet, "./new_img/%s", chemin_sortie);
                programme_quantification1(chemin_complet, chemin_sortie_complet, K);
                
                printf("Image générée avec %d couleurs (mapping1 - RGB) : %s\n", K, chemin_sortie_complet);
                break;
            }

            case 3: {
                char chemin_complet[200];
                char chemin_sortie_complet[250];
                printf("Nom exacte de l'image (elle doit être dans ./ressources/IMAGES/): ");
                scanf("%s", chemin_image);
                
                printf("Nombre de couleurs K : ");
                scanf("%d", &K);
                
                printf("Nom du fichier de sortie : ");
                scanf("%s", chemin_sortie);
                
                sprintf(chemin_complet, "./ressources/IMAGES/%s", chemin_image);
                sprintf(chemin_sortie_complet, "./new_img/%s", chemin_sortie);
                programme_quantification2(chemin_complet, chemin_sortie_complet, K);
                
                printf("Image générée avec %d couleurs (mapping2 - CIELAB) : %s\n", K, chemin_sortie_complet);
                break;
            }

            case 4:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
                break;
        }
    } while(choix != 4);

    return 0;
}

