#include "Plane.h"
#include "Ray.h"
#include "Vec3.h"

Plane::Plane(const Point3& position, const Color& color, const float reflectivity,
             const Vec3& normal, const float rotation, const float width, const float height) :
  Body(position, color, reflectivity),
  norm_(unit_vector(normal)), dims_{ width, height }
{}

float Plane::hit(const Ray& ray) const {
  float t = dot(norm_, (this->get_pos() - ray.origin()))/dot(norm_, ray.direction());

  // Check this is within the bounds of the plane
  //    Vec3 hitpos = ray.at(t) - pos; // Vector to hit from centre
  //    if (hitpos.x() < dims[0] && hitpos.x() > dims[0] && hitpos.y() < dims[1] && hitpos.y() > dims[1])
  return t;
  //    else
  //        return -1.0;
}

Vec3 Plane::normal_at(const Point3& other_pos) const { return norm_; }

Color Plane::color_at(const Point3& other_pos) const { return this->get_base_color(); }
