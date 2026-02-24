#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "image.h"


image create_image()
{
  image img=(image)malloc(sizeof(struct image));

  assert(img);
  
  img->dim=img->width=img->height=img->max_val = 0;
  img->data=NULL;

  return img;
}

void init_from_file(image img,char* file)
{    
  FILE *f = fopen(file,"rb");
  char buf[50];
  int line = 0; /* shows the first line where colors are write */

  assert(f);
  assert(img);       

  /* Read line dimension */
  fgets(buf, sizeof(buf), f);
  line++;
  sscanf(buf, "P%d", &img -> dim);
  
  /* Read line width height */
  do {
    fgets(buf, sizeof(buf), f);
    line++;
  } while( buf[0] == '#');
  if ( sscanf(buf, "%d %d", &(img->width), &(img->height)) != 2)
    printf("Erreur de lecture du fichier"); 

  /* Read line max_val */
  fgets(buf,sizeof(buf), f);
  line++;
  sscanf(buf, "%d", &img -> max_val);

  switch(img-> dim){
    case 2 : {
      init_P2(img, f, img->max_val);
      break;
    }
    case 3 : {
      init_P3(img, f, img->max_val);
      break;
    }
    case 5 : {
      init_P5(img, f, img->max_val);
      break;
    }
    case 6 : {
      init_P6(img, f, img->max_val);
      break;
    }
  }
  fclose(f);
}




void init_P2(image img, FILE *f, int maxval){
  int pixels = img->width * img->height;
  int bytes_per_pixel = (maxval < 256) ? 1 : 2;
  int index = 0;
  int value;
  int i;

  img->data = malloc(pixels * bytes_per_pixel * sizeof(unsigned char));

  for(i = 0; i < pixels; i++)
  {
    fscanf(f, "%d", &value);
    img->data[index++] = value;
    if(bytes_per_pixel == 2)
      img->data[index++] = value >> 8;
  }
}




void init_P3(image img, FILE *f, int maxval){
  int pixels = img->width * img->height;
  int bytes_per_component = (maxval < 256) ? 1 : 2;
  int index = 0;
  int value;
  int i, c;

  img->data = malloc(pixels * 3 * bytes_per_component * sizeof(unsigned char));

  for(i = 0; i < pixels; i++)
  {
    for(c = 0; c < 3; c++)
    {
      fscanf(f, "%d", &value);
      img->data[index++] = value;
      if(bytes_per_component == 2)
        img->data[index++] = value >> 8;
    }
  }
}




void init_P5(image img, FILE *f, int maxval){
  int pixels = img->width * img->height;
  int bytes_per_pixel = (maxval < 256) ? 1 : 2;
  int index = 0;
  unsigned char byte;
  int i;

  img->data = malloc(pixels * bytes_per_pixel * sizeof(unsigned char));

  for(i = 0; i < pixels; i++)
  {
    fread(&byte, 1, 1, f);
    img->data[index++] = byte;
    if(bytes_per_pixel == 2){
      fread(&byte, 1, 1, f);
      img->data[index++] = byte;
    }
  }
}

void init_P6(image img, FILE *f, int maxval){
  int pixels = img->width * img->height;
  int bytes_per_component = (maxval < 256) ? 1 : 2;
  int index = 0;
  unsigned char byte;
  int i, c;

  img->data = malloc(pixels * 3 * bytes_per_component * sizeof(unsigned char));

  for(i = 0; i < pixels; i++)
  {
    for(c = 0; c < 3; c++)
    {
      fread(&byte, 1, 1, f);
      img->data[index++] = byte;
      if(bytes_per_component == 2){
        fread(&byte, 1, 1, f);
        img->data[index++] = byte;
      }
    }
  }
}



