#include "plane.h"
#include "ray.h"
#include "vec3.h"

Plane::Plane(unsigned int id_, float reflectivity_,
             Point3 position, Color color, Vec3 normal,
             float rotation, float width, float height) :
  col(color),
  norm(unit_vector(normal)), dims{ width, height }
{
  id = id_;
  reflectivity = reflectivity_;
  pos = position;
}

float Plane::hit(const Ray& ray) const {
  float t = dot(norm, (pos - ray.origin()))/dot(norm, ray.direction());

  // Check this is within the bounds of the plane
  //    Vec3 hitpos = ray.at(t) - pos; // Vector to hit from centre
  //    if (hitpos.x() < dims[0] && hitpos.x() > dims[0] && hitpos.y() < dims[1] && hitpos.y() > dims[1])
  return t;
  //    else
  //        return -1.0;
}

Vec3 Plane::normal_at(const Point3& other_pos) const { return norm; }

Color Plane::color_at(const Point3& other_pos) const { return col; }
