#include <memory>
#include <vector>
#include "World.h"
#include "Vec3.h"
#include "Sphere.h"
#include "Ground.h"
#include "Plane.h"

World::World() {
  bodies = {
    std::make_shared<Sphere>(Vec3(-0.5,  0.0, -1.0), Color(0.0, 1.0, 0.0), 0.0, 0.3),
    std::make_shared<Sphere>(Vec3( 0.5,  0.0, -1.1), Color(1.0, 1.0, 1.0), 1.0, 0.3),
    std::make_shared<Sphere>(Vec3(-0.2, -0.5, -1.5), Color(1.0, 1.0, 1.0), 1.0, 0.2),

    std::make_shared<Ground>(-0.5, Color(1.0, 1.0, 1.0), 0.0),
    // std::make_shared<Plane>(3, 0.0, Point3(0.0, -0.4, -1.5), Color(1.0, 1.0, 0.0), Vec3(0.0, 1.0, 0.1), 1.0, 100.0, 100.0),
  };

  lights = {
    Light(Point3(0.0, 1000.0, 1000.0), Color(1.0, 1.0, 1.0)),
  };
}
