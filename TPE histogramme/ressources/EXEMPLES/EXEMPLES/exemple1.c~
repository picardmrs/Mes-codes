#include <image.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
  image img;
  Point P;
  int* pix;
  
  img=FAIRE_image();
  image_charger(img,argv[1]);

  COORDX(P)=COORDY(P)=0;
  image_move_to(img,&P);
  pix=image_lire_pixel(img);

  printf("(R,G,B)=(%d,%d,%d)\n",pix[0],pix[1],pix[2]);

  COORDX(P)=image_give_largeur(img)-1;
  COORDY(P)=image_give_hauteur(img)-1;

  image_move_to(img,&P);
  pix=image_lire_pixel(img);
  printf("(R,G,B)=(%d,%d,%d)\n",pix[0],pix[1],pix[2]);

  DEFAIRE_image(img);
  exit(0);
}
