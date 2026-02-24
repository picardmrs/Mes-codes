#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "image.h"
#include "convert.h"

void convert_P2_to_P5(image img, char* output_file)
{
  FILE *f = fopen(output_file, "wb");
  int pixels = img->width * img->height;
  int bytes_per_pixel = (img->max_val < 256) ? 1 : 2;

  fprintf(f, "P5\n");
  fprintf(f, "%d %d\n", img->width, img->height);
  fprintf(f, "%d\n", img->max_val);

  fwrite(img->data, 1, pixels * bytes_per_pixel, f);
  fclose(f);
}

void convert_P5_to_P2(image img, char* output_file)
{
  FILE *f = fopen(output_file, "w");
  int pixels = img->width * img->height;
  int bytes_per_pixel = (img->max_val < 256) ? 1 : 2;
  int index = 0;
  int value;
  int i;

  fprintf(f, "P2\n");
  fprintf(f, "%d %d\n", img->width, img->height);
  fprintf(f, "%d\n", img->max_val);

  for(i = 0; i < pixels; i++)
  {
    if(bytes_per_pixel == 1){
      value = img->data[index++];
    } else {
      value = img->data[index] * 256 + img->data[index + 1];
      index += 2;
    }
    fprintf(f, "%d ", value);
    if((i + 1) % img->width == 0)
      fprintf(f, "\n");
  }
  fprintf(f, "\n");
  fclose(f);
}

void convert_P3_to_P6(image img, char* output_file)
{
  FILE *f = fopen(output_file, "wb");
  int pixels = img->width * img->height;
  int bytes_per_component = (img->max_val < 256) ? 1 : 2;

  fprintf(f, "P6\n");
  fprintf(f, "%d %d\n", img->width, img->height);
  fprintf(f, "%d\n", img->max_val);

  fwrite(img->data, 1, pixels * 3 * bytes_per_component, f);
  fclose(f);
}

void convert_P6_to_P3(image img, char* output_file)
{
  FILE *f = fopen(output_file, "w");
  int pixels = img->width * img->height;
  int bytes_per_component = (img->max_val < 256) ? 1 : 2;
  int index = 0;
  int value;
  int i, c;

  fprintf(f, "P3\n");
  fprintf(f, "%d %d\n", img->width, img->height);
  fprintf(f, "%d\n", img->max_val);

  for(i = 0; i < pixels; i++)
  {
    for(c = 0; c < 3; c++)
    {
      if(bytes_per_component == 1){
        value = img->data[index++];
      } else {
        value = img->data[index] * 256 + img->data[index + 1];
        index += 2;
      }
      fprintf(f, "%d ", value);
    }
    if((i + 1) % img->width == 0)
      fprintf(f, "\n");
  }
  fprintf(f, "\n");
  fclose(f);
}
