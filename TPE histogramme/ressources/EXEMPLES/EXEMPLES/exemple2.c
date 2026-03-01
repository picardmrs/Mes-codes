#include <image.h>
#include <stdio.h>

void usage(char* cmd)
{
  fprintf(stderr,"Usage: %s file alpa R G B > result.ppm",cmd);
}
int main(int argc,char* argv[])
{
  image img;
  int* pix;
  int i,vitre[3],color[3];
  int dim;  
  float alpha;
  
  if(argc!= 6)
    {
      usage(argv[0]);
      exit(1);
    }

  img=FAIRE_image();
  image_charger(img,argv[1]);
  dim=image_give_dim(img);
  alpha=atof(argv[2]);
  for(i=0;i<dim;i++)
    vitre[i]=atoi(argv[3+i]);

  image_debut(img);
  do
    {
      pix=image_lire_pixel(img);
      for(i=0;i<dim;i++)
	{
	  color[i]=(int)(pix[i]*alpha+vitre[i]*(1.0-alpha));
	  image_ecrire_pixel(img,color);
	}
    }
  while(image_pixel_suivant(img));

  image_to_stream(img,stdout);
  DEFAIRE_image(img);
  exit(0);
}
      
    
  
