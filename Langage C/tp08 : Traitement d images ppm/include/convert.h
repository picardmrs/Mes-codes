#ifndef __CONVERT__
#define __CONVERT__

#include "image.h"

extern void convert_P2_to_P5(image img, char* output_file);
extern void convert_P5_to_P2(image img, char* output_file);
extern void convert_P3_to_P6(image img, char* output_file);
extern void convert_P6_to_P3(image img, char* output_file);

#endif
