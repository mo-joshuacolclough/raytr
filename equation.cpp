#include "equation.h"
#include "body.h"
#include "vec3.h"
#include "ray.h"

Equation::Equation(unsigned int id_, Color color, float (*f_)(float, float)) :
  id(id_), reflectivity(0.0), pos(0.0, 0.0, 0.0), col(color), f(f_)
{}

float Equation::hit(const Ray& ray) const {
  return f()
}

Vec3 Equation::normal_at(const Point3& other_pos) const {
  return Vec3(0.0, 1.0, 0.0);
}

Color Equation::color_at(const Point3& other_pos) const { return col; }
