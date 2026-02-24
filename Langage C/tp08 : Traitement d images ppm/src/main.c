#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "convert.h"

#define MAX 256

void menu_display(char *menu[])
{
  int i = 1;

  printf("%s", menu[0]);
  while(menu[i] != NULL){
    printf("%d. %s\n", i, menu[i]);
    i++;
  }
}

int main()
{
  image img;
  char input_file[MAX];
  char output_file[MAX];
  int choix;
  char *menu[] = {
    "======== MENU PPM/PGM ========\n",
    "Load file",
    "Convert P2 in P5",
    "convert P5 in P2",
    "convert P3 in P6",
    "convert P6 in P3",
    "Quitter",
    NULL
  };

  img = create_image();

  do{
    menu_display(menu);
    printf("\nChoose a number : ");
    scanf("%d", &choix);

    switch(choix){
      case 1 :
        printf("Enter file name please : ");
        scanf("%s", input_file);
        init_from_file(img, input_file);
        printf("File load\n");
        printf("Format: P%d\n\n", img->dim);
        break;

      case 2 :
        if(img->data == NULL){
          printf("No image load\n\n");
          break;
        }
        printf("Enter file name please : ");
        scanf("%s", output_file);
        convert_P2_to_P5(img, output_file);
        printf("Good file in P5\n\n");
        if(img->data != NULL)
          free(img->data);
        break;

      case 3 :
        if(img->data == NULL){
          printf("No image load\n\n");
          break;
        }
        printf("Enter file name please : ");
        scanf("%s", output_file);
        convert_P5_to_P2(img, output_file);
        printf("Good file in P2\n\n");
        if(img->data != NULL)
          free(img->data);
        break;

      case 4 :
        if(img->data == NULL){
          printf("No image load\n\n");
          break;
        }
        printf("Enter file name please : ");
        scanf("%s", output_file);
        convert_P3_to_P6(img, output_file);
        printf("Good file in P6\n\n");
        if(img->data != NULL)
          free(img->data);
        break;

      case 5 :
        if(img->data == NULL){
          printf("No image load\n\n");
          break;
        }
        printf("Enter file name please : ");
        scanf("%s", output_file);
        convert_P6_to_P3(img, output_file);
        printf("Good file in P3\n\n");
        if(img->data != NULL)
          free(img->data);
        break;

      case 6 :
        printf("Leave\n");
        break;

      default :
        printf("Error retry\n\n");
    }
  } while(choix != 6);

  free(img->data);
  free(img);
  return 0;
}
