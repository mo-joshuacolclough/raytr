#include <cmath>
#include <cstdlib>
#include "ground.h"
#include "ray.h"
#include "vec3.h"

#define CHECK_DIST 0.1

Ground::Ground(unsigned int id_, float yval, Color color) {
  id = id_;
  col = color;
  pos[1] = yval;
  reflectivity = 0.0;
}

float Ground::hit(const Ray& ray) const {
  if (ray.direction().y() > 0.0) {
    return -1.0;
  }

  return (pos[1] - ray.origin().y())/ray.direction().y();
}

Vec3 Ground::normal_at(const Point3 &other_pos) const {
  return Vec3(0.0, 1.0, 0.0);
}

Color Ground::color_at(const Point3 &other_pos) const {
  /*
  Vec3 dist_vec = pos - other_pos;
  bool white = (static_cast<int>(std::round(std::abs(dist_vec.x())/CHECK_DIST)) % 2) ^
               (static_cast<int>(std::round(std::abs(dist_vec.z())/CHECK_DIST)) % 2);
  */
  bool white = true;

  return Color(white, white, white);
}
