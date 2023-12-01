#pragma once

#include "Vec3.h"


class Light {
 public:
  Light(const Point3& position, const Color& color);
  const Point3& get_pos() const { return pos_; }
  const Color& get_color() const { return col_; }
 private:
  Point3 pos_;
  Color col_;
};

