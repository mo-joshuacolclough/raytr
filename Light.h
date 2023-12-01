#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"


class Light {
 public:
  Point3 pos;
  Color col;
  Light(Point3 position, Color color);
};

#endif // LIGHT_H
