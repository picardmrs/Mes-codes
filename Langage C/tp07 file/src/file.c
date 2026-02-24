#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "file.h"


struct cellule{
    int valeur;
    struct cellule* suiv;
};

typedef struct cellule cellule;

struct cellule_d{
    int valeur ;
    struct cellule* suiv;
    struct cellule* prec;
};

typedef struct cellule_d cellule_d;

struct file_cl{
    struct cellule* tete;
    struct cellule* queue;
};

struct file_circ{
    struct cellule* queue;
};

/** PARTIE 1 : File classique **/

file_cl creer_file_cl(){

  file_cl file= (file_cl)malloc(sizeof(struct file_cl));

  assert(file);
    
  file->tete =NULL;
  file->queue = NULL;

  return file;
}

bool empty_file_cl(file_cl file){
  return (file->tete == NULL);
}

void enfiler_file_cl(file_cl file, int valeur){
  cellule* cel;
    
  assert(file);
  
  cel = (cellule*)malloc(sizeof(cellule));
  cel->valeur = valeur;
  cel->suiv = NULL;
  if (empty_file_cl(file))
    file->tete = cel;
  else
    file->tete->suiv = cel;
  
  
  file->queue = cel;
}

void defiler_file_cl(file_cl file){
    cellule* tmp;

    if( empty_file_cl(file))
        {
            fprintf(stderr,"Rien à défiler");
            return;
        } 

    tmp = file->tete; 
    file->tete = file->tete->suiv;
    free(tmp);
}

file_cl concatenate(file_cl file1, file_cl file2)
{
        file1->queue->suiv = file2->tete;
        file1->queue = file2->tete;
    return file1;
}

int affiche(file_cl file)
{
    cellule* adresse = file->tete;
    while(adresse != NULL){
        printf("%d ",adresse->valeur);
        adresse = adresse->suiv;
    }

    return 0; 
}


/** PARTIE 2 : File circulaire **/

file_circ creer_file_circ(){

  file_circ file= (file_circ)malloc(sizeof(struct file_circ));

  assert(file);
    
  file->queue = NULL;

  return file;
}

bool empty_file_circ(file_circ file){
  return (file->queue == NULL);
}

void enfiler_file_circ(file_circ file, int valeur)
{
  cellule* cel;
    
  assert(file);
  
  cel = (cellule*)malloc(sizeof(cellule));
  cel->valeur = valeur;
  if (empty_file_circ(file)){
    cel->suiv = cel;
    file->queue = cel;
  } 
  else {
    cel->suiv = file->queue->suiv;
    file->queue->suiv = cel;
    file->queue = cel;
  }
}

void defiler_file_circ(file_circ file){
    cellule* tmp;

    if( empty_file_circ(file))
        {
            fprintf(stderr,"Rien à défiler");
            return;
        } 

    tmp = file->queue->suiv;
    if(tmp == file->queue){
        file->queue = NULL;
    } 
    else {
        file->queue->suiv = tmp->suiv;
    }
    free(tmp);
}

file_circ concatenate_file_circ(file_circ file1, file_circ file2)
{
    cellule* start1;
    cellule* start2;
    if(empty_file_circ(file1)){
        file1->queue = file2->queue;
    } else if(!empty_file_circ(file2)){
        start1 = file1->queue->suiv;
        start2 = file2->queue->suiv;
        file1->queue->suiv = start2;
        file2->queue->suiv = start1;
        file1->queue = file2->queue;
    }
    return file1;
}

int affiche_circ(file_circ file)
{
    cellule* adresse;
    if(empty_file_circ(file)){
      return 0;
    }
      
    adresse = file->queue->suiv;
    do{
        printf("%d ",adresse->valeur);
        adresse = adresse->suiv;
    }while(adresse != file->queue->suiv);

    return 0; 
}


















