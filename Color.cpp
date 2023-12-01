#include <iostream>
#include <cmath>
#include "Vec3.h"
#include "Color.h"

void write_color(std::ostream& out, Color pixel_color) {
  /*
  float r = std::sqrt(pixel_color[0]/2);
  float g = std::sqrt(pixel_color[1]/2);
  float b = std::sqrt(pixel_color[2]/2);
  */

  float r = pixel_color[0] * 1.2;
  float g = pixel_color[1] * 1.2;
  float b = pixel_color[2] * 1.2;

  out << static_cast<int>(255.999 * r) << ' '
      << static_cast<int>(255.999 * g) << ' '
      << static_cast<int>(255.999 * b) << '\n';
}
