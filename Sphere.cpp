#include "Sphere.h"
#include "Body.h"
#include "Vec3.h"
#include "Ray.h"
#include <cmath>

Sphere::Sphere(const Point3& centre, const Color& color, const float reflectivity, const float radius) :
  Body(centre, color, reflectivity), r_(radius)
{}

float Sphere::hit(const Ray& ray) const {
  // Maths again from https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/ - 6.2
  const Vec3 oc = ray.origin() - this->get_pos();
  const float a = ray.direction().length_squared();
  const float b = 2.0 * dot(oc, ray.direction());
  const float c = oc.length_squared() - r_ * r_;
  const float discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - std::sqrt(discriminant))/(2.0 * a);
  }
}

Vec3 Sphere::normal_at(const Point3& other_pos) const {
  const Vec3 dist_vec = other_pos - this->get_pos();
  return unit_vector(dist_vec);
}

Color Sphere::color_at(const Point3& other_pos) const { return this->get_base_color(); }

/*
Color Sphere::color_at(const Point3& other_pos) const {
    Vec3 norm = normal_at(other_pos);

    bool white = static_cast<int>(std::round(std::abs(norm.x() * 4.0))) % 2 ^
                 static_cast<int>(std::round(std::abs(norm.z() * 4.0))) % 2;
                 // static_cast<int>(std::round(std::abs(norm.z() * 4.0))) % 2;

    return white * col;
}
*/
