#include <memory>
#include <vector>
#include "world.h"
#include "vec3.h"
#include "sphere.h"
#include "ground.h"
#include "plane.h"

World::World() {
  bodies = {
    std::make_shared<Sphere>(0, 0.0, Vec3(-0.5, 0.0, -1.0), 0.3, Color(0.0, 1.0, 0.0)),// Color(1.0, 0.0, 0.0)),
    std::make_shared<Sphere>(1, 1.0, Vec3(0.5, 0.0, -1.1), 0.3, Color(1.0, 1.0, 1.0)), // Color(0.0, 1.0, 0.0)),
    std::make_shared<Sphere>(2, 1.0, Vec3(-0.2, -0.5, -1.5), 0.2, Color(1.0, 1.0, 1.0)), // Color(0.0, 1.0, 0.0)),
    

    std::make_shared<Ground>(10000, -0.5, Color(1.0, 1.0, 1.0)),
    // std::make_shared<Plane>(3, 0.0, Point3(0.0, -0.4, -1.5), Color(1.0, 1.0, 0.0), Vec3(0.0, 1.0, 0.1), 1.0, 100.0, 100.0),
  };

  lights = {
    Light(Point3(0.0, 1000.0, 1000.0), Color(1.0, 1.0, 1.0)),
  };
}
