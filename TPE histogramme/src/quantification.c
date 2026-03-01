#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quantification.h"
#include "histogramme.h"
#include "image.h"



int* quantification(histo h, int* tab, int K) {
    int* freqs;
    int count = 0;
    histo_iter iter;
    int indice;
    int couleur_temp[3];
    int freq_temp;
    int couleur_bonus[3];
    int existe;
    int i;
    
    freqs = (int*)malloc(K * sizeof(int));
    
    iter = create_histo_iter(h);
    start_histo_iter(iter, h);

    /* K premières couleurs */
    give_color_histo_iter(iter, couleur_temp);
    rgb_bonus(couleur_temp[0], couleur_temp[1], couleur_temp[2], &couleur_bonus[0], &couleur_bonus[1], &couleur_bonus[2]);
    
    tab[0] = couleur_bonus[0];
    tab[1] = couleur_bonus[1]; 
    tab[2] = couleur_bonus[2];
    freqs[0] = give_freq_histo_iter(iter);
    count = 1;

    while (count < K && next_histo_iter(iter,h)){
        indice = count;
        give_color_histo_iter(iter, couleur_temp);
        rgb_bonus(couleur_temp[0], couleur_temp[1], couleur_temp[2], &couleur_bonus[0], &couleur_bonus[1], &couleur_bonus[2]);
        freq_temp = give_freq_histo_iter(iter);
        
        /* on verife que la couleur est pas dans tab si elle y est pas on la rajoute*/
        existe = 0;
        for (i = 0; i < count; i++) {
            if (tab[i*3] == couleur_bonus[0] && tab[i*3+1]== couleur_bonus[1] && tab[i*3+2]== couleur_bonus[2]) {
                existe = 1;
                break;
            }
        }
        
        if (!existe) {
            while ( ( indice > 0 ) && ( freqs[indice-1] < freq_temp ) ){
                freqs[indice] = freqs[indice-1];
                tab[indice*3] = tab[(indice-1)*3];
                tab[indice*3 + 1] = tab[(indice-1)*3 + 1];
                tab[indice*3 + 2] = tab[(indice-1)*3 + 2];
                indice = indice-1;
            }
            tab[indice*3] = couleur_bonus[0];
            tab[indice*3 + 1] = couleur_bonus[1];
            tab[indice*3 + 2] = couleur_bonus[2];
            freqs[indice] = freq_temp;
            count++;
        }
    }

    /* Autres couleurs */
    while (next_histo_iter(iter, h)){
        give_color_histo_iter(iter, couleur_temp);
        rgb_bonus(couleur_temp[0], couleur_temp[1], couleur_temp[2], &couleur_bonus[0], &couleur_bonus[1], &couleur_bonus[2]);

        freq_temp = give_freq_histo_iter(iter);
                
        /* On verifie que la couleur bonus n est pas dans tab si elle y est pas on rajoute mais on regarde aussi fréquence avant */
        existe = 0;
        for (i = 0; i < count; i++) {
            if (tab[i*3] == couleur_bonus[0] && tab[i*3+1] == couleur_bonus[1] && tab[i*3+2] == couleur_bonus[2]) {
                existe = 1;
                break;
            }
        }

        if (!existe && freq_temp > freqs[K-1]){
            indice = K - 1;
            while ( ( indice > 0 ) && ( freqs[indice-1] < freq_temp ) ){
                freqs[indice] = freqs[indice-1];
                tab[indice*3] = tab[(indice-1)*3];
                tab[indice*3 + 1] = tab[(indice-1)*3 + 1];
                tab[indice*3 + 2] = tab[(indice-1)*3 + 2];
                indice = indice-1;
            }
            tab[indice*3] = couleur_bonus[0];
            tab[indice*3 + 1] = couleur_bonus[1];
            tab[indice*3 + 2] = couleur_bonus[2];
            freqs[indice] = freq_temp;
        }
    }
    free(freqs);
    delete_histo_iter(iter);
    return tab;
}

void rgb_bonus(int R, int G, int B, int* qR, int* qG, int* qB) {
	*qR = (R / 2) * 2;
	*qG = G;
	*qB = (B / 4) * 4;
}

void mapping1(image input, image output, int* tab, int K){
	int k;
	int* pixel_rgb;
	int min_index;
	int min_distance;
	int distance;
	int new_pixel[3];

	image_debut(input);
	image_debut(output);

	do {
		pixel_rgb = image_lire_pixel(input);

		min_index = 0;
		min_distance = abs(pixel_rgb[0] - tab[0*3]) + abs(pixel_rgb[1] - tab[0*3 + 1]) + abs(pixel_rgb[2] - tab[0*3 + 2]);

		for (k = 1; k < K; k++){
			distance = abs(pixel_rgb[0] - tab[k*3]) + abs(pixel_rgb[1] - tab[k*3 + 1]) + abs(pixel_rgb[2] - tab[k*3 + 2]);
			if (distance < min_distance){
				min_distance = distance;
				min_index = k;
			}
		}

		new_pixel[0] = tab[min_index*3];
		new_pixel[1] = tab[min_index*3 + 1];
		new_pixel[2] = tab[min_index*3 + 2];

		image_ecrire_pixel(output, new_pixel);
		image_pixel_suivant(output);
	} while (image_pixel_suivant(input));
}

double inverse_gamma(double valeur_normalisee) {
	double a = 0.055;
	if (valeur_normalisee <= 0.04045) {
		return valeur_normalisee / 12.92;
	} 
    else {
		return pow((valeur_normalisee + a) / (1.0 + a), 2.4);
	}
}

double f(double t) {
	double delta = 6.0 / 29.0;
	if(t > delta * delta * delta) {
		return pow(t, 1.0 /3.0);
	} 
    else{
		return (t / (3.0 * delta * delta)) + (4.0 / 29.0);
	}
}

void rgb_to_lab(int R, int G, int B, double* L, double* a, double* b) {
	double Rn, Gn, Bn;
	double R_lin, G_lin, B_lin;
	double X, Y, Z;
	double x, y, z;
	double fx, fy, fz;
	
	/* Normalisation */
	Rn = R / 255.0;
	Gn = G / 255.0;
	Bn = B / 255.0;
	
	/* Gamma inverse */
	R_lin = inverse_gamma(Rn);
	G_lin = inverse_gamma(Gn);
	B_lin = inverse_gamma(Bn);
	
	/* RGB -> XYZ */
	X = R_lin * 0.4124564 + G_lin * 0.3575761 + B_lin * 0.1804375;
	Y = R_lin * 0.2126729 + G_lin * 0.7151522 + B_lin * 0.0721750;
	Z = R_lin * 0.0193339 + G_lin * 0.1191920 + B_lin * 0.9503041;
	
	/* Normalisation par rapport au blanc de reference */
	x = X / 0.95047;
	y = Y / 1.0;
	z = Z / 1.08883;
	
	/* Application de f(t) */
	fx = f(x);
	fy = f(y);
	fz = f(z);
	
	/* Calcul final de L, a et b */
	*L = 116.0 * fy - 16.0;
	*a = 500.0 * (fx - fy);
	*b = 200.0 * (fy - fz);
}

void mapping2(image input, image output, int* tab, int K) {
	int k;
	int* pixel_rgb;
	int min_index;
	double min_distance;
	double distance;
	int new_pixel[3];
	double L_pixel, a_pixel, b_pixel;
	double L_k, a_k, b_k;
	double dL, da, db;

	image_debut(input);
	image_debut(output);

	do {
		pixel_rgb = image_lire_pixel(input);
		
		/* Conversion du pixel en CIELAB */
		rgb_to_lab(pixel_rgb[0], pixel_rgb[1], pixel_rgb[2], &L_pixel, &a_pixel, &b_pixel);

		/* Recherche de la couleur la plus proche */
		min_index = 0;
		rgb_to_lab(tab[0], tab[1], tab[2], &L_k, &a_k, &b_k);
		dL = L_pixel - L_k;
		da = a_pixel - a_k;
		db = b_pixel - b_k;
		min_distance = sqrt(dL*dL + da*da + db*db);

		for (k = 1; k < K; k++) {
			rgb_to_lab(tab[k*3], tab[k*3 + 1], tab[k*3 + 2], &L_k, &a_k, &b_k);
			dL = L_pixel - L_k;
			da = a_pixel - a_k;
			db = b_pixel - b_k;
			distance = sqrt(dL*dL + da*da + db*db);
			
			if (distance < min_distance) {
				min_distance = distance;
				min_index = k;
			}
		}

		new_pixel[0] = tab[min_index*3];
		new_pixel[1] = tab[min_index*3 + 1];
		new_pixel[2] = tab[min_index*3 + 2];

		image_ecrire_pixel(output, new_pixel);
		image_pixel_suivant(output);
	} while (image_pixel_suivant(input));
}

void programme_quantification1(char* chemin_input, char* chemin_output, int K) {
	int* tab;
	image input, output;
	histo h;
	int hauteur, largeur;

	input = FAIRE_image();
	image_charger(input, chemin_input);
	
	hauteur = image_give_hauteur(input);
	largeur = image_give_largeur(input);
	
	if (hauteur <= 0 || largeur <= 0) {
		printf("Erreur : impossible de charger l'image\n");
		DEFAIRE_image(input);
		return;
	}
	
	output = FAIRE_image();
	image_initialize(output, 3, largeur, hauteur);

	h = create_histo();
	init_histo(h, input);
	
	tab = (int*)malloc(K * 3 * sizeof(int));
	quantification(h, tab, K);
	
	mapping1(input, output, tab, K);
	
	image_sauvegarder(output, chemin_output);
	
	free(tab);
	delete_histo(h);
	DEFAIRE_image(input);
	DEFAIRE_image(output);
}

void programme_quantification2(char* chemin_input, char* chemin_output, int K) {
	int* tab;
	image input, output;
	histo h;
	int hauteur, largeur;

	input = FAIRE_image();
	image_charger(input, chemin_input);
	
	hauteur = image_give_hauteur(input);
	largeur = image_give_largeur(input);
	
	if (hauteur <= 0 || largeur <= 0) {
		printf("Erreur : impossible de charger l'image\n");
		DEFAIRE_image(input);
		return;
	}
	
	output = FAIRE_image();
	image_initialize(output, 3, largeur, hauteur);

	h = create_histo();
	init_histo(h, input);
	
	tab = (int*)malloc(K * 3 * sizeof(int));
	quantification(h, tab, K);
	
	mapping2(input, output, tab, K);
	
	image_sauvegarder(output, chemin_output);
	
	free(tab);
	delete_histo(h);
	DEFAIRE_image(input);
	DEFAIRE_image(output);
}


