#include "sphere.h"
#include "body.h"
#include "vec3.h"
#include "ray.h"
#include <cmath>

Sphere::Sphere(unsigned int id_, float reflectivity_,
               Point3 centre, float radius, Color color) :
  r(radius), col(color)
{
  id = id_;
  reflectivity = reflectivity_;
  pos = centre;
}

float Sphere::hit(const Ray& ray) const {
  // Maths again from https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/ - 6.2
  Vec3 oc = ray.origin() - pos;
  float a = ray.direction().length_squared();
  float b = 2.0 * dot(oc, ray.direction());
  float c = oc.length_squared() - r*r;
  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - std::sqrt(discriminant))/(2.0 * a);
  }

  /*
    bool not_hit = discriminant < 0;
    return (not_hit * -1.0) + ((!not_hit) * (-b - std::sqrt(discriminant))/(2.0 * a));
    */
}

Vec3 Sphere::normal_at(const Point3& other_pos) const {
  Vec3 dist_vec = other_pos - pos;
  return unit_vector(dist_vec);
}

Color Sphere::color_at(const Point3& other_pos) const { return col; }

/*
Color Sphere::color_at(const Point3& other_pos) const {
    Vec3 norm = normal_at(other_pos);

    bool white = static_cast<int>(std::round(std::abs(norm.x() * 4.0))) % 2 ^
                 static_cast<int>(std::round(std::abs(norm.z() * 4.0))) % 2;
                 // static_cast<int>(std::round(std::abs(norm.z() * 4.0))) % 2;

    return white * col;
}
*/
