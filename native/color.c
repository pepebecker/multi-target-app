#include "color.h"

uint32_t convert_color_to_uint32(Color c) {
  return ((uint32_t)c.a << 24) | ((uint32_t)c.b << 16) | ((uint32_t)c.g << 8) | ((uint32_t)c.r);
}
