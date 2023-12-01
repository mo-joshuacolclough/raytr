#pragma once

#include <vector>
#include <memory>
#include "Vec3.h"
#include "Body.h"
#include "Light.h"

typedef std::vector<std::shared_ptr<Body>> BodyList;

class World {
 public:
  BodyList bodies;
  std::vector<Light> lights;
  World();
};

