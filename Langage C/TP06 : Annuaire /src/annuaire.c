#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personne.h"
#include "annuaire.h"

#define taille 1000

/**
 * @file Ensemble des fonctions permettant de travailler sur un annuaire 
 * @brief Crée un annuaire vide
 *
 * Ce fichier contient l'ensemble des fonctions permettant de :
 * - Créer un nouvel annuaire vide
 * - Ajouter une personne à l'annuaire (avec vérification de la taille maximale)
 * - Supprimer une personne de l'annuaire (par nom)
 * - Sauvegarder l'annuaire dans un fichier texte (annuaire.txt)
 * - Charger un annuaire depuis un fichier texte
 * - Afficher toutes les informations de l'annuaire (nom, prénom, téléphone, âge)
 *
 * @author PICARD Marius
 * @date 19/11/2025
 */

annuaire* create_empty_annuaire(int nb_pers){
    annuaire* anu = malloc(sizeof(annuaire));

    anu->nb_personnes = 0;
    anu->allocated_personne = nb_pers;
    anu->p = malloc(sizeof(personne) * nb_pers);

    return anu;
}


void ajt_personnes(annuaire* anu,
                   char* prenom,
                   char* nom,
                   char* num_tel,
                   int age){
    
    if(anu->nb_personnes >= anu->allocated_personne){
        anu->allocated_personne += BLOCK_SIZE;
        anu->p = realloc(anu->p, sizeof(personne) * anu->allocated_personne);
    }

    strcpy(anu->p[anu->nb_personnes].prenom, prenom);
    strcpy(anu->p[anu->nb_personnes].nom, nom);
    strcpy(anu->p[anu->nb_personnes].tel, num_tel);
    anu->p[anu->nb_personnes].age = age;
    anu->nb_personnes++;
}

void supp_personne(annuaire* anu,
                    char* nom){

    int i=0;

    
    while (i < anu->nb_personnes && strcmp(anu->p[i].nom,nom)!=0){ 
        i++;
    }

    if (i < anu->nb_personnes) {
        memmove(anu->p + i, anu->p + i + 1, (anu->nb_personnes - i - 1) * sizeof(personne));
        anu->nb_personnes--;
    }
}


void sauvegarder_anu(annuaire* anu){
   int i;
   FILE *f = fopen("ressource/annuaire.txt","w");
    if (!f){
        printf("Erreur ouverture fichier\n");
        return ; 
    }

    for (i=0; i < anu->nb_personnes; i++){
        fprintf(f,"%s;%s;%s;%d;\n",anu->p[i].nom,anu->p[i].prenom,anu->p[i].tel,anu->p[i].age);
    }
    fclose(f);
    printf("Sauvegarde terminée\n");
}


void charger_anu(annuaire* anu){
   char ligne[256];
   char* token;
   int count = 0;

   FILE *f = fopen("ressource/annuaire.txt","r");
    if (!f){
        printf("Erreur ouverture fichier\n");
        return ; 
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        if (count >= anu->allocated_personne) {
            anu->allocated_personne += BLOCK_SIZE;
            anu->p = realloc(anu->p, anu->allocated_personne * sizeof(personne));
        }
        
        token = strtok(ligne,";");
        if (token != NULL)
            strcpy(anu->p[count].nom, token);
        token = strtok(NULL,";");
        if (token != NULL)
            strcpy(anu->p[count].prenom, token);       
        token = strtok(NULL,";");
        if (token != NULL)
            strcpy(anu->p[count].tel, token);
        token = strtok(NULL,";");
        if (token != NULL)
            anu->p[count].age = atoi(token);
        count++;
    }
    anu->nb_personnes = count;
    fclose(f);
    printf("Chargement terminé\n");
}


void afficher_annuaire(annuaire* anu){

    int i=0;

    for (i=0;i<anu->nb_personnes;i++){
        printf("%s;%s;%s;%d\n",anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
    }
}

void rechercher_une_personne_nom(annuaire* anu,char* nom){
    
    int trouve = 0;
    char* rech = nom;
    int i;
    
    if (nom[strlen(nom)-1] == '*') {
        rech = malloc(strlen(nom));
        strcpy(rech, nom);
        rech[strlen(rech)-1] = '\0';
    }
    
    for(i=0; i<anu->nb_personnes;i++){
        if (nom[strlen(nom)-1] == '*' && strncmp(anu->p[i].nom, rech, strlen(rech)) == 0) {
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        } else if (nom[strlen(nom)-1] != '*' && strcmp(anu->p[i].nom, nom) == 0) {
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("Aucun résultat\n");
    
    if (nom[strlen(nom)-1] == '*') free(rech);
}



void rechercher_une_personne_prenom(annuaire* anu, char* prenom){
    
    int trouve = 0;
    char* rech = prenom;
    int i;
    
    if (prenom[strlen(prenom)-1] == '*') {
        rech = malloc(strlen(prenom));
        strcpy(rech, prenom);
        rech[strlen(rech)-1] = '\0';
    }
    
    for(i=0;i<anu->nb_personnes;i++){
        if (prenom[strlen(prenom)-1] == '*' && strncmp(anu->p[i].prenom, rech, strlen(rech)) == 0) {
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        } else if (prenom[strlen(prenom)-1] != '*' && strcmp(anu->p[i].prenom, prenom) == 0) {
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("Aucun résultat\n");
    
    if (prenom[strlen(prenom)-1] == '*') free(rech);
}


void rechercher_une_personne_age(annuaire* anu, int age){
    
    int trouve = 0;
    int i;
    
    for(i=0;i<anu->nb_personnes;i++){
        if(anu->p[i].age == age){
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("Aucun résultat\n");
}

int match_tel(char* tel, char* pattern) {
    size_t len = strlen(pattern);
    size_t i;
    if (strlen(tel) != len) return 0;
    for (i = 0; i < len; i++) {
        if (pattern[i] != '?' && pattern[i] != tel[i]) return 0;
    }
    return 1;
}

void rechercher_une_personne_tel(annuaire* anu, char* tel){

    int trouve = 0;
    int i;
    
    for(i=0; i<anu->nb_personnes; i++){
        if(match_tel(anu->p[i].tel, tel)){
            printf("Nom: %s Prénom: %s Téléphone: %s Âge: %d\n", anu->p[i].nom, anu->p[i].prenom, anu->p[i].tel, anu->p[i].age);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("Aucun résultat\n");
}





