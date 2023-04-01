#include <cmath>
#include "vec3.h"
#include "color.h"

color_t get_color_t(Color pixel_color) {
  float r = pixel_color[0] * 1.2;
  float g = pixel_color[1] * 1.2;
  float b = pixel_color[2] * 1.2;

  return C_RGB(static_cast<color_t>(31 * r),
	       static_cast<color_t>(31 * g),
	       static_cast<color_t>(31 * b));

}
