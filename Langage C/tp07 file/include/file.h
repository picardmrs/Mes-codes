#ifndef __FILE_H__
#define __FILE_H__

#include "bool.h"

typedef struct file_cl *file_cl;
typedef struct file_circ *file_circ;


file_cl creer_file_cl();
bool empty_file_cl(file_cl);
void enfiler_file_cl(file_cl,int);
void defiler_file_cl(file_cl);
file_cl concatenate(file_cl, file_cl);
int affiche(file_cl);

file_circ creer_file_circ();
bool empty_file_circ(file_circ);
void enfiler_file_circ(file_circ,int);
void defiler_file_circ(file_circ);
file_circ concatenate_file_circ(file_circ, file_circ);
int affiche_circ(file_circ);
  

#endif
