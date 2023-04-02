#include <cmath>
#include "vec3.h"
#include "color.h"

color_t get_color_t(Color pixel_color) {
  return C_RGB(static_cast<color_t>(31.0 * pixel_color[0]),
	       static_cast<color_t>(31.0 * pixel_color[1]),
	       static_cast<color_t>(31.0 * pixel_color[2]));

}
