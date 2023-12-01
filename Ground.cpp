#include <cmath>
#include <cstdlib>
#include "Ground.h"

#define CHECK_DIST 0.1

Ground::Ground(const float yval, const Color& color, const float reflectivity) :
  Body(Point3(0.0, yval, 0.0), color, reflectivity)
{}

float Ground::hit(const Ray& ray) const {
  if (ray.direction().y() > 0.0)
    return -1.0;
  
  return (this->get_pos()[1] - ray.origin().y())/ray.direction().y();
}

Vec3 Ground::normal_at(const Point3& other_pos) const {
  return Vec3(0.0, 1.0, 0.0);
}

Color Ground::color_at(const Point3& other_pos) const {
  const Vec3 dist_vec = this->get_pos() - other_pos;
  const bool white = (static_cast<int>(std::round(std::abs(dist_vec.x())/CHECK_DIST)) % 2) ^
                     (static_cast<int>(std::round(std::abs(dist_vec.z())/CHECK_DIST)) % 2);

  return Color(white, white, white);
}
