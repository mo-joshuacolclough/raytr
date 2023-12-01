#include "torus.h"
#include "vec3.h"
#include "ray.h"

Torus::Torus(Point3 centre, Vec3 centre_norm_, float major_rad_, float minor_rad_)
  : pos(centre), centre_norm(centre_norm_), major_rad(major_rad_), minor_rad(minor_rad_) {}

Torus::Torus(Point3 centre, Vec3 centre_norm, float major_rad) {
  // doughnut ratio of 2/3
  Torus(centre, centre_norm, major_rad, 0.66666 * major_rad);
}

float Torus::hit(const Ray& ray) const
{
  // TODO
}

Vec3 Torus::normal_at(const Point3 &other_pos) const {
  Vec3 dist_vec = other_pos - pos;
  return unit_vector(dist_vec);
}
