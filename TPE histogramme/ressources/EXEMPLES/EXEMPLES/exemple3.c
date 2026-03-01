#include <image.h>
#include <stdio.h>

void usage(char* cmd)
{
  fprintf(stderr,"Usage: %s file alpa radius R G B > result.ppm",cmd);
}
int main(int argc,char* argv[])
{
  image img;
  int* pix;
  int i,vitre[3],color[3];
  int dim;  
  float alpha,radius;
  Point P;
  float x0,y0,dist;
  
  if(argc!= 7)
    {
      usage(argv[0]);
      exit(1);
    }

  img=FAIRE_image();
  image_charger(img,argv[1]);
  dim=image_give_dim(img);
  alpha=atof(argv[2]);
  radius=atof(argv[3]);
  for(i=0;i<dim;i++)
    vitre[i]=atoi(argv[4+i]);

  x0=image_give_largeur(img)/2;
  y0=image_give_hauteur(img)/2;

  
  image_debut(img);
  COORDX(P)=COORDY(P)=0;

  do
    {
      do
	{
	  dist=(x0-COORDX(P))*(x0-COORDX(P))+(y0-COORDY(P))*(y0-COORDY(P));
	  if(dist<= radius*radius)
	    {
	      pix=image_lire_pixel(img);
	      for(i=0;i<dim;i++)
		{
		  color[i]=(int)(pix[i]*alpha+vitre[i]*(1.0-alpha));
		  image_ecrire_pixel(img,color);
		}
	    }
	  COORDX(P)++;
	}
      while(image_pixel_droite(img));
      COORDX(P)=0;
      COORDY(P)++;
    }
  while(image_pixel_suivant(img));


  image_to_stream(img,stdout);
  DEFAIRE_image(img);
  exit(0);
}
      
    
  
