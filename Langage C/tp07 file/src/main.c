#include <stdio.h>
#include "bool.h"
#include "file.h"

#define NB_FILE 10

void menu_display(char * menu[]){
    int i = 1; 
    
    printf("%s", menu[0]);

    while(menu[i]!=NULL){
        printf("%d, %s",i,menu[i]);
        i++;
    }
}

int main(){
    int choix;
    int nb;
    int nb2;
    int type;
    char* menu[NB_FILE] = {"======Menu======\n","créer file vide\n","tester file vide\n","enfiler un élement\n","defiler un element\n","concatener deux files\n","afficher le contenu de la file\n","Quitter\n"};
    file_cl file_classic[NB_FILE];
    file_circ file_circ[NB_FILE];
    int val;

    do{
        printf("Choisissez le type de file:\n1. File classique\n2. File circulaire\n3. Quitter\n");
        scanf("%d",&type);
        
        if(type == 3) break;
        if(type != 1 && type != 2) continue;
        
        do{
            menu_display(menu);
            scanf("%d",&choix);
        
            switch(choix){
                case 1 :
                    printf("\nNum de la file dans [0,%d] : ",NB_FILE-1);
                    scanf("%d",&nb);
                    if(type == 1)
                        file_classic[nb] = creer_file_cl();
                    else
                        file_circ[nb] = creer_file_circ();
                    break;

                case 2 :
                    printf("\nNum de la file dans [0,%d] : ",NB_FILE-1);
                    scanf("%d",&nb);
                    if(type == 1){
                        if (empty_file_cl(file_classic[nb]))
                            printf("la file est vide\n");
                        else 
                            printf("la file n'est pas vide\n");
                    } else {
                        if (empty_file_circ(file_circ[nb]))
                            printf("la file est vide\n");
                        else 
                            printf("la file n'est pas vide\n");
                    }
                    break;

                case 3 :
                    printf("\nNum de la file dans [0,%d] :",NB_FILE-1);
                    scanf("%d",&nb);
                    printf("\nvaleur à ajouter : ");
                    scanf("%d",&val);
                    if(type == 1)
                        enfiler_file_cl(file_classic[nb],val);
                    else
                        enfiler_file_circ(file_circ[nb],val);
                    break;

                case 4 : 
                    printf("\nNum de la file dans [0,%d] : ",NB_FILE-1);
                    scanf("%d",&nb);
                    if(type == 1)
                        defiler_file_cl(file_classic[nb]);
                    else
                        defiler_file_circ(file_circ[nb]);
                    break;

                case 5 : 
                    printf("\nNum de la premiere file dans [0,%d] : ",NB_FILE-1);
                    scanf("%d",&nb);
                    printf("\nNum de la seconde file dans [0,%d] : ",NB_FILE-1);
                    scanf("%d",&nb2);
                    if(type == 1)
                        concatenate(file_classic[nb],file_classic[nb2]);
                    else
                        concatenate_file_circ(file_circ[nb],file_circ[nb2]);
                    break;

                case 6 :
                    printf("\nNum de la file dans [0,%d] :",NB_FILE-1);
                    scanf("%d",&nb);
                    if(type == 1)
                        affiche(file_classic[nb]);
                    else
                        affiche_circ(file_circ[nb]);
                    break;
            }
        }while(choix != 7);
    }while(type != 3);
    
    return 0;
}
