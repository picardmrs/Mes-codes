#include <stdio.h>
#include "annuaire.h"
#include "personne.h"

/*
 On déclare les varianles et les cnstantes qui nous seront utiles 
 * */

#define MAX 10
#define NONE NULL



int main(){
    int choix;
    int choix2;
    annuaire* anu = NULL;
    
    do {
        printf("\n=== Annuaire téléphonique ===\n");
        printf("1. Créer un annuaire\n");
        printf("2. Ajouter une personne\n");
        printf("3. Supprimer une personne\n");
        printf("4. Sauvegarder l'annuaire\n");
        printf("5. Charger l'annuaire\n");
        printf("6. Afficher l'annuaire\n");
        printf("7. Rechercher une personne\n");
        printf("8. Quitter\n");
        printf("Votre choix (numéro): ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int nb_pers;

                printf("Nombre personnes annuaire : ");
                scanf("%d",&nb_pers);

                anu = create_empty_annuaire(nb_pers);
                break;
            }

            case 2: {
                char prenom[STR_SIZE];
                char nom[STR_SIZE];
                char num_tel[STR_SIZE];
                int age;

                printf("Rentrer les infos suivantes :\nPrénom : ");
                scanf("%49s", prenom);
                printf("Nom : ");
                scanf("%49s", nom);
                printf("Numéro de téléphone : ");
                scanf("%49s", num_tel);
                printf("age : ");
                scanf("%d", &age);

                ajt_personnes(anu,prenom,nom,num_tel,age);
                break;
            }

            case 3: {
                char nom[STR_SIZE];
                printf("Nom : ");
                scanf("%49s", nom);

                supp_personne(anu,nom);
                break;
            }

            case 4:
                sauvegarder_anu(anu);
                break;

            case 5:
                charger_anu(anu);
                break;

            case 6:
                afficher_annuaire(anu);
                break;

            case 7: {
                 printf("\n===== MENU RECHERCHE =====\n");
                 printf("1. Rechercher une personne par NOM (* joker)\n");
                 printf("2. Rechercher une personne par PRENOM (* joker)\n");
                 printf("3. Rechercher une personne par TELEPHONE (? joker)\n");
                 printf("4. Rechercher une personne par AGE\n");
                 printf("5. Rechercher un numero de telephone par PREFIXE (*)\n");

                 scanf("%d", &choix2);

                switch(choix2){
                    
                    case 1: {
                        char nom[STR_SIZE]; 
                        printf("Nom : ");
                        scanf("%49s", nom);         
                        rechercher_une_personne_nom(anu, nom);
                        break;
                    }
                    
                    case 2: {
                        char prenom[STR_SIZE];
                        printf("Prenom : ");
                        scanf("%49s", prenom);
                        rechercher_une_personne_prenom(anu,prenom);
                        break;
                    }
                   

                    case 3: {
                        char tel[STR_SIZE];
                        printf("Téléphone : ");
                        scanf("%49s", tel);
                        rechercher_une_personne_tel(anu,tel);
                        break;
                    }

                    case 4: {
                            int age;
                            printf("Age : ");
                            scanf("%d", &age);
                            rechercher_une_personne_age(anu,age);
                            break;
                        }
                        
                    case 5: {
                        
                        break;
                    }
                        

                }
                break;
            }

            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 8);

    return 0;
}
