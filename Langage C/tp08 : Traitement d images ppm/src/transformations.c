#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transformations.h"
#include "image.h"

/* Fonction generique pour appliquer une matrice de transformation (convolution)*/
void appliquer_filtre(image img, int x_min,int y_min, int x_max, int y_max, double matrice[3][3], double diviseur){
    int x,y, c, pos, val;
    double somme;
    unsigned char *tmp = (unsigned char*)malloc(3* img->width * img->height);
    
    memcpy(tmp,img->data, 3 * img->width* img->height);

    for(y= y_min; y <= y_max; y++){
        for(x = x_min; x<= x_max; x++){
            pos = 3 * (y* img->width + x);
            for(c = 0; c < 3; c++){
                somme = matrice[0][0] * tmp[3*((y-1)*img->width + x-1) + c] +
                        matrice[0][1] * tmp[3*((y-1)* img->width + x) + c] +
                        matrice[0][2] * tmp[3*((y-1)*img->width + x+1) + c] +
                        matrice[1][0] * tmp[3*(y*img->width + x-1) + c] +
                        matrice[1][1] * tmp[3*(y*img->width+ x) + c] +
                        matrice[1][2] * tmp[3*(y*img->width + x+1) + c] +
                        matrice[2][0] * tmp[3*((y+1)*img->width + x-1) + c]+
                        matrice[2][1] * tmp[3*((y+1)*img->width + x) + c] +
                        matrice[2][2] * tmp[3*((y+1)*img->width + x+1) + c];
                val = somme/ diviseur + 0.5;
                if(val < 0) val =0;
                if(val > 255) val= 255;
                img->data[pos + c] = val;
            }
        }
    }
    free(tmp);
}

extern void seuillage(int val, char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit){
    int i, x, y;
    int x_min, y_min, x_max, y_max;
    FILE *f;
    int pixels;
    int bytes_per_component;
    int index;
    int value;
    int c;
    image img;
    int moy_ponderee;
    int pos;

    /* on cree et on initialise l'image */
    img = create_image();
    init_from_file(img, img_entree);

    if((img->dim == 2) || (img->dim == 5)){
        printf("ERREUR: Le fichier en entrée n'est pas au format PPM");
        return;
    }

    /* on applique le seuillage*/
    /* gestion de la partie de l'image sur laquel est appliqué le filtre*/
    if(sup_gauche[0]>=0 && sup_gauche[1]>=0){
        x_min = sup_gauche[0];
        y_min = sup_gauche[1];
    } else {
        x_min = 0;
        y_min = 0;
    }

    if(inf_droit[0]>=0 && inf_droit[1]>=0) {
        x_max = inf_droit[0];
        y_max = inf_droit[1];
        if(x_max >= img->width) x_max = img->width - 1;
        if(y_max >= img->height) y_max = img->height - 1;
    } else {
        x_max = img->width - 1;
        y_max = img->height - 1;
    }

    /* Parcours rectangle par rectangle (ligne par ligne, colonne par colonne)*/
    for(y = y_min; y<= y_max; y++){
        for(x = x_min; x <= x_max; x++){
            pos = 3 * (y* img->width + x);
            /* on utilise une moyenne ponderee car les humains ne percoivent pas les rgb de la meme maniere*/
            moy_ponderee = 0.299*img->data[pos] + 0.587*img->data[pos+1]+ 0.114*img->data[pos+2];
            if(moy_ponderee < val){
                img->data[pos] = 0;
                img->data[pos+1]= 0;
                img->data[pos+2] = 0;
            }
        }
    }

    /* on cree la nouvelle image*/
    f = fopen(img_sortie, "w");
    pixels = img->width * img->height;
    bytes_per_component = (img->max_val < 256) ? 1 : 2;
    index = 0;

    fprintf(f, "P%d\n", img->dim);
    fprintf(f, "%d %d\n", img->width, img->height);
    fprintf(f, "%d\n", img->max_val);

    for(i = 0; i < pixels; i++)
    {
        for(c = 0; c < 3; c++)
        {
        if(bytes_per_component == 1){
            value = img->data[index++];
        } else {
            value = img->data[index] * 256 + img->data[index + 1];
            index += 2;
        }
        fprintf(f, "%d ", value);
        }
        if((i + 1) % img->width == 0)
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    fclose(f);
    
    free(img->data);
    free(img);

}

extern void gradient( char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit){
    int i, x, y;
    int x_min, y_min, x_max, y_max;
    FILE *f;
    int pixels;
    int bytes_per_component;
    int index;
    int value;
    int c;
    image img;
    double gx, gy, norme;
    int pos, w;

    img = create_image();
    init_from_file(img, img_entree);

    if((img->dim == 2) || (img->dim == 5)){
        printf("ERREUR: Le fichier en entrée n'est pas au format PPM");
        return;
    }

    w = img->width;
    x_min = (sup_gauche[0] >= 0)? sup_gauche[0] : 1;
    y_min = (sup_gauche[1] >= 0) ? sup_gauche[1]: 1;
    x_max = (inf_droit[0] >= 0 && inf_droit[0] < w-1)? inf_droit[0] : w-2;
    y_max = (inf_droit[1] >= 0 && inf_droit[1] < img->height-1) ? inf_droit[1]: img->height-2;

    for(y = y_min; y <= y_max; y++){
        for(x = x_min; x<= x_max; x++){
            pos = 3 * (y * w+ x);
            for(c = 0; c< 3; c++){
                gx = (img->data[3*(y*w + x+1) + c] - img->data[3*(y*w + x-1) + c])/ 2.0;
                gy = (img->data[3*((y+1)*w + x) + c] - img->data[3*((y-1)*w+ x) + c]) / 2.0;
                norme = sqrt(gx* gx + gy * gy);
                img->data[pos + c] = (norme > 255)? 255 : (unsigned char)(norme + 0.5);
            }
        }
    }

    f = fopen(img_sortie, "w");
    pixels = img->width * img->height;
    bytes_per_component = (img->max_val < 256) ? 1 : 2;
    index = 0;

    fprintf(f, "P%d\n", img->dim);
    fprintf(f, "%d %d\n", img->width, img->height);
    fprintf(f, "%d\n", img->max_val);

    for(i = 0; i < pixels; i++)
    {
        for(c = 0; c < 3; c++)
        {
            if(bytes_per_component == 1){
                value = img->data[index++];
            } else {
                value = img->data[index] * 256 + img->data[index + 1];
                index += 2;
            }
            fprintf(f, "%d ", value);
        }
        if((i + 1) % img->width == 0)
            fprintf(f, "\n");
    }
    fprintf(f, "\n");
    fclose(f);
    
    free(img->data);
    free(img);
}

extern void lissage( char* img_entree, char* img_sortie, int* sup_gauche, int* inf_droit){
    int i, x_min, y_min, x_max, y_max;
    FILE *f;
    int pixels;
    int bytes_per_component;
    int index;
    int value;
    int c;
    image img;
    double matrice_lissage[3][3] = {{1.0, 1.0, 1.0},{1.0, 1.0, 1.0},{1.0, 1.0, 1.0}};

    img = create_image();
    init_from_file(img, img_entree);

    if((img->dim == 2) || (img->dim == 5)){
        printf("ERREUR: Le fichier en entrée n'est pas au format PPM");
        return;
    }

    if(sup_gauche[0]>=0 && sup_gauche[1]>=0){
        x_min = sup_gauche[0];
        y_min = sup_gauche[1];
    } else{
        x_min = 1;
        y_min = 1;
    }

    if(inf_droit[0]>=0 && inf_droit[1]>=0){
        x_max = inf_droit[0];
        y_max = inf_droit[1];
        if(x_max >= img->width - 1) x_max = img->width- 2;
        if(y_max >= img->height - 1) y_max= img->height - 2;
    } else {
        x_max = img->width - 2;
        y_max = img->height- 2;
    }

    appliquer_filtre(img, x_min, y_min,x_max, y_max, matrice_lissage, 9.0);

    f = fopen(img_sortie, "w");
    pixels = img->width * img->height;
    bytes_per_component = (img->max_val < 256) ? 1 : 2;
    index = 0;

    fprintf(f, "P%d\n", img->dim);
    fprintf(f, "%d %d\n", img->width, img->height);
    fprintf(f, "%d\n", img->max_val);

    for(i = 0; i < pixels; i++)
    {
        for(c = 0; c < 3; c++)
        {
            if(bytes_per_component == 1){
                value = img->data[index++];
            } else {
                value = img->data[index] * 256 + img->data[index + 1];
                index += 2;
            }
            fprintf(f, "%d ", value);
        }
        if((i + 1) % img->width == 0)
            fprintf(f, "\n");
    }
    fprintf(f, "\n");
    fclose(f);
    
    free(img->data);
    free(img);
}
