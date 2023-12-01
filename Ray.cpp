#include "Ray.h"
#include "Vec3.h"
#include <iostream>

Ray::Ray(const Point3& origin, const Vec3& direction, const double brightness) :
  origin_(origin), dir_(unit_vector(direction)), brightness_(brightness)
{}

Ray::Ray(const Point3& origin, const Vec3& direction) :
  Ray(origin, direction, 1.0)
{}

const Point3& Ray::origin() const { return origin_; }
const Vec3& Ray::direction() const { return dir_; }
Point3 Ray::at(const float t) const { return origin_ + t * dir_; }

Ray Ray::reflect(const Vec3& normal,
                 const Vec3& new_origin,
                 const double reflectivity) const {
  return Ray(new_origin, dir_ - 2 * dot(dir_, normal) * normal, brightness_);
}
