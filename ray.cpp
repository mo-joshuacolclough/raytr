#include "ray.h"
#include "vec3.h"

Ray::Ray() : brightness(1.0) {}

Ray::Ray(const Point3& origin, const Vec3& direction) :
  o(origin), dir(unit_vector(direction)), brightness(1.0)
{}

Ray::Ray(const Point3& origin, const Vec3& direction, const float brightness) :
  o(origin), dir(unit_vector(direction)), brightness(brightness)
{}


Point3 Ray::origin() const { return o; }
Vec3 Ray::direction() const { return dir; }
Point3 Ray::at(float t) const { return o + t * dir; }

void Ray::reflect(const Vec3& normal,
                  Vec3 new_origin,
                  const float reflectivity) {
  o = new_origin;
  dir = dir - 2 * dot(dir, normal) * normal;
}
