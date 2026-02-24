#ifndef __ANNUAIRE_H__
#define __ANNUAIRE_H__

#include "personne.h"

#define BLOCK_SIZE 100

typedef struct {
  personne* p;
  int nb_personnes;
  int allocated_personne;
} annuaire;

extern annuaire* create_empty_annuaire(int);
extern void ajt_personnes(annuaire*, char*, char*, char*, int);
extern void supp_personne(annuaire*, char*);
extern void sauvegarder_anu(annuaire*);
extern void charger_anu(annuaire*);
extern void afficher_annuaire(annuaire*);
extern void rechercher_une_personne_nom(annuaire*, char*);
extern void rechercher_une_personne_prenom(annuaire*, char*);
extern void rechercher_une_personne_age(annuaire*, int);
extern void rechercher_une_personne_tel(annuaire*, char*);

#endif
