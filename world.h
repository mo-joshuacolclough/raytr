#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "vec3.h"
#include "body.h"
#include "light.h"

typedef std::vector<std::shared_ptr<Body>> BodyList;

class World {
public:
  BodyList bodies;
  std::vector<Light> lights;
  World();
};

#endif // WORLD_H
