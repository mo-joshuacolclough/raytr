#ifndef EQUATION_H
#define EQUATION_H

#include "vec3.h"
#include "ray.h"
#include "body.h"

class Equation : public Body {
 private:
  Color col;
  float (*f)(float, float);  // f(x, y)
  float(*f_dx)(float, float, float); // d/dx partial. Both needed for finding surface normal
  float(*f_dy)(float, float, float); // d/dy partial

public:
  Equation(unsigned int id, Color color, float (*f)(float, float));
  float hit(const Ray& r) const override;
  Vec3 normal_at(const Point3& pos) const override;
  Color color_at(const Point3& pos) const override;
};


#endif // EQUATION_H
