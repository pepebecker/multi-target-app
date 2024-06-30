#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

uint32_t convert_color_to_uint32(Color c);

#endif // __COLOR_H__
