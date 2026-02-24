#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef __IMAGE__
#define __IMAGE__

struct image{
  int dim;
  int width;
  int height;
  int max_val;
  unsigned char* data;
};

typedef struct image* image;

extern image create_image();
extern void init_from_file(image,char*);
extern void init_P2(image img, FILE *f, int maxval);
extern void init_P3(image img, FILE *f, int maxval);
extern void init_P5(image img, FILE *f, int maxval);
extern void init_P6(image img, FILE *f, int maxval);

#endif
