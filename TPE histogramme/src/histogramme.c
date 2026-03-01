#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "histogramme.h"
#include "image.h"
#include <math.h>

/* Definition des structures */
struct cell {
    unsigned char B;
    int freq;
    struct cell *next;
};

struct pixel {
	int R;
	int G;
	int B;
};

/*
struct image {
	int lenght;
	int width;
	pixel *pixel;
};
*/

struct histo_iter {
	int R,G;
	cell current;
};

/* Code des fonctions */

/* Partie 2.1 */

cell create_cell(int B, cell next){
	cell cellule;
	cellule = (cell)malloc(sizeof(* cellule));
	assert(cellule);

	cellule -> B = B;
	cellule -> next = next;
	cellule -> freq = 1;	

	return cellule;
}

cell insert_cell(cell head, int B){

	cell curr = head;
	cell prev = NULL;
	cell newcell;

	while ( curr != NULL && curr -> B < B){
		prev = curr;
		curr = curr -> next;
	}

	if (curr != NULL && curr -> B == B){
		curr -> freq += 1;
		return head;
	}
	
	newcell = create_cell(B, curr);
	
	if (prev == NULL){
		return newcell;
	}
	
	prev -> next = newcell;
	return head;
}

cell delete_list(cell list) {
	cell tmp;
	while (list != NULL){
		tmp = list -> next;
		free(list);
		list = tmp;
	}
	return NULL;
}

/* Partie 2.2 */

histo create_histo(void){
	int i,j;
	histo histogramme;

	histogramme = malloc(N * sizeof(cell *));
	assert(histogramme);

	for (i=0; i < N; i++){
		histogramme[i] = malloc (N * sizeof (cell));
		assert(histogramme[i]);
		for (j=0; j < N; j++){
			histogramme[i][j] = NULL;
		}
	}

	return histogramme;
}

void init_histo(histo histo, image img){
	int i, j;
	int R, G, B;
	int* pixel_rgb;
	int hauteur = image_give_hauteur(img);
	int largeur = image_give_largeur(img);
	
	for (i=0; i < hauteur; i++){
		for (j=0; j < largeur; j++){
			pixel_rgb = image_get_pixel(img, i, j);
			R = pixel_rgb[0];
			G = pixel_rgb[1];
			B = pixel_rgb[2];
			
			if (histo[R][G] == NULL){
				histo[R][G] = create_cell(B, NULL);
			} 
			else {
				histo[R][G] = insert_cell(histo[R][G], B);
			}
		}
	}
}


void delete_histo(histo h){
	int i,j;
	for(i=0; i<256; i++){
		for(j=0; j<256; j++){
			delete_list(h[i][j]);
		}
		free(h[i]);
	}
	free(h);
}

/* Partie 2.3 */

int give_freq_histo(histo h,int R,int G,int B){
        cell curr;

        if (h == NULL)
                return 0;

        curr = h[R][G];
        while (curr != NULL){
                if (curr->B == B)
                        return curr->freq;
                curr = curr->next;
        }
        return 0;
}

int give_freq_histo_iter(histo_iter iter){
	return iter -> current -> freq;
}

histo_iter create_histo_iter(histo h){
	int i = 0, j = 0; 
	histo_iter iter = malloc(sizeof(struct histo_iter));
	
	assert(h);
	assert(iter);
	
	while (h[i][j] == NULL && i < N) {
		j++;
		if (j == N) {
			j = 0;
			i++;
		}
	}
	assert(i < N);
	
	iter->R = i;
	iter->G = j;
	iter->current = h[i][j];
	return iter;	
}

void start_histo_iter(histo_iter iter, histo h){
	int i = 0, j = 0;

	assert(h);
	assert(iter);

	while (h[i][j] == NULL && i < N) {
		j++;
		if (j == N) {
			j = 0;
			i++;
		}
	}
	assert(i < N);

	iter->R = i;
	iter->G = j;
	iter->current = h[i][j];

}

boolean next_histo_iter(histo_iter iter, histo h){
	int i , j;
	
	if (iter->current == NULL)
		return false;

	else if (iter->current->next != NULL) {
			iter->current = iter->current->next;
			return true;
	}
	
	else{
		i = iter -> R;
		j = iter -> G + 1;

		while(i < N){
			while(j < N){
				if(h[i][j] != NULL){
					iter -> R = i;
					iter -> G = j;
					iter -> current = h[iter->R][iter->G];

					return true;
				}
				j++;
			}
			j = 0;
			i++;
		}
	}
	return false; 
}


void give_color_histo_iter(histo_iter iter,int* couleur){
	couleur[0] = iter -> R;
	couleur[1] = iter -> G;
	couleur[2] = iter -> current -> B;
}


void delete_histo_iter(histo_iter iter){
	free(iter);
}


/* 3 Implémentation ppmhist */

void histo_display(char* chemin_image){
    int couleur[3];
    int freq;
    int lum;
    int result; 
    char chemin_complet[100];
	
    image img = FAIRE_image();  /* On créée l image */
    histo h = create_histo();   /* On créée l'histo */
    histo_iter iter;  /* Déclaration de iter */

    strcpy(chemin_complet, "./ressources/IMAGES/");
    strcat(chemin_complet, chemin_image);

    result = image_charger(img, chemin_complet);
    
	if (result != 0) {
        printf("!! Image introuvable !!\n");
        DEFAIRE_image(img);
        delete_histo(h);
        return;
    }
                
    init_histo(h, img); /* On remplit l'histo de l'image */
    iter = create_histo_iter(h); /* On créée histo_iter après init */

    printf("INFOS HSTOGRAMME : \nR, G, B, Luminosité, Fréquence\n");
    do{
        give_color_histo_iter(iter, couleur); 
        lum = (couleur[0] + couleur[1] + couleur[2])/3;
        freq = give_freq_histo(h, couleur[0], couleur[1], couleur[2]);

        printf("%d, %d, %d, %d, %d\n", couleur[0], couleur[1], couleur[2], lum, freq);
    } while (next_histo_iter(iter,h));

    /* On libere la mémoire */
    if (result == 0) {
        DEFAIRE_image(img);
    }
    delete_histo_iter(iter);
    delete_histo(h);
}



