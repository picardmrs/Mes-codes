#include "personne.h"
#include <assert.h>
#include <string.h>

int compare_age(personne*p,int age)
{
  assert(p);

  return p->age-age;
}
void copy_personne(personne*p1,
		   personne*p2)
{
  assert(p1);
  assert(p2);
  
  strncpy(p1->nom, p2->nom, 100);
  strncpy(p1->prenom, p2->prenom, 100);
  strncpy(p1->tel, p2->tel, 100);
  strncpy(p1->age, p2->age,100);
}
