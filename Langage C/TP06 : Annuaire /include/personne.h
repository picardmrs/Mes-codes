#define STR_SIZE 50

/**
 * @file personne.h
 * @brief Définition de la structure personne.
 *
 * Ce fichier contient la structure principale représentant une personne.
 * @author PICARD Marius
 * @date 19/11/2025
 */

#ifndef __PERSONNE_H__
#define __PERSONNE_H__

struct personne {
    char nom[STR_SIZE];
    char prenom[STR_SIZE];
    char tel[STR_SIZE];
    int age;
    struct personne **ami; 
    int nb_amis;            
};

typedef struct personne personne; 

#endif 

