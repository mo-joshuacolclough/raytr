#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <fstream>

#include <SDL2/SDL.h>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "body.h"
#include "sphere.h"
#include "light.h"
#include "ground.h"
#include "world.h"
#include "plane.h"

#define MAX_REFLECT 2


Color ray_color(const Ray& r, const World& world, Color last_col, unsigned int depth) {
  float t = -1.0; // position along ray of closest hit
  std::shared_ptr<Body> hitobj; // object that was hit

  for (const std::shared_ptr<Body>& b : world.bodies) {
    float dist = b->hit(r);

    if (dist > 0.0 && (t < 0.0 || t > dist)) {
      hitobj = b;
      t = dist;
    }
  }

  if (t > 0.0) {    // If the ray hits something
    Vec3 hitpos = r.at(t);
    Color final_col = hitobj->color_at(hitpos) * last_col;
    Vec3 hitnorm = hitobj->normal_at(hitpos);

    // For each light, combine color
    // also check if light is blocked by another object
    const float numLightf = static_cast<float>(world.lights.size());
    for (const Light& l : world.lights) {
      // Get direction to light from hit pos
      Vec3 dir = l.pos - hitpos;
      Vec3 dir_unit = unit_vector(dir);

      Ray shadowray = Ray(hitpos, dir_unit);
      for (const std::shared_ptr<Body>& b : world.bodies) {
        if (b->id != hitobj->id) {
          float d = b->hit(shadowray);
          if (d > 0.0) return Color(0.0, 0.0, 0.0);
        }
      }

      // dot product with normal = lighting
      float d = dot(unit_vector(dir), hitnorm);
      d = d < 0.0 ? 0.0 : d;
      final_col[0] *= l.col[0] * d / numLightf;
      final_col[1] *= l.col[1] * d / numLightf;
      final_col[2] *= l.col[2] * d / numLightf;
    }

    // Reflect and call again
    if (depth < MAX_REFLECT && hitobj->reflectivity != 0.0) {
      Ray reflected = r.reflect(hitnorm, hitpos, hitobj->reflectivity);
      final_col = ray_color(reflected, world, final_col, depth+1);
    }

    Vec3 n = unit_vector(r.at(t) - hitobj->pos);
    if (r.getBrightness() < 1.0) {
      std::cout << "Ray brightness: " << r.getBrightness() << std::endl;
    }
    return final_col * r.getBrightness();
  }

  t = 0.5 * (r.direction().y() + 1.0);
  return last_col * ((1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0));
}

namespace {

Vec3 rotate_y(Vec3 in, float a) {
  Vec3 out;
  out[0] = in[0] * cos(a) + in[2] * sin(a);
  out[1] = in[1];
  out[2] = in[2] * cos(a) - in[0] * sin(a);
  return out;
}

inline Uint32 to_pixel(SDL_Surface* surface, Color color) {
  return SDL_MapRGBA(surface->format,
                     static_cast<uint8_t>(color[0] * 255),
                     static_cast<uint8_t>(color[1] * 255),
                     static_cast<uint8_t>(color[2] * 255),
                     255);
}

}  // namespace


int main() {
  // Following https://raytracing.github.io/books/RayTracingInOneWeekend.html
  
  constexpr float aspect_ratio = 16.0/9.0;
  //    const float aspect_ratio = 1.0;
  constexpr int image_width = 1920 / 2;
  constexpr int image_height = static_cast<int>(image_width/aspect_ratio);

  SDL_Window* window = nullptr;
  SDL_Surface* screen_surface = nullptr;
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Raytr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image_width, image_height, SDL_WINDOW_SHOWN );

  screen_surface = SDL_GetWindowSurface(window);

  // Scene
  World world = World();

  // Camera (maths from https://raytracing.github.io/books/RayTracingInOneWeekend.html)
  float viewport_height = 2.0;
  float viewport_width = aspect_ratio * viewport_height;
  float focal_length = 1.0;

  Point3 origin = Point3(0, 0, 0);
  float camera_y_angle = 0.2;
  // float camera_x_angle = 0.0;

  Vec3 horizontal = Vec3(viewport_width, 0, 0);
  Vec3 vertical = Vec3(0, viewport_height, 0);

  Vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

  bool quit = false;
  float a = 0.0;

  //Event handler
  SDL_Event e;

  while(!quit) {
    while(SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Update
    a += 0.2;
    world.bodies[0]->pos.y() = (std::sin(a) / 4.0) + 0.25;
    
    // Draw

    // Lock screen image
    SDL_LockSurface(screen_surface);
    Uint32 *buffer = (Uint32*)screen_surface->pixels;

    #pragma omp parallel for
    for (int j = 0; j < image_height; ++j) {
      for (int i = 0; i < image_width; ++i) {
        float u = static_cast<float>(i)/(image_width-1);
        float v = static_cast<float>(j)/(image_height-1);
        Vec3 ray_direction = lower_left_corner + u * horizontal + v * vertical - origin;
        ray_direction = rotate_y(ray_direction, camera_y_angle);

        buffer[(image_height - j - 1) * image_width + i] = to_pixel(screen_surface, ray_color(Ray(origin, ray_direction), world, Color(1.0, 1.0, 1.0), 0));
      }
    }
    SDL_UnlockSurface(screen_surface);

    //Update the surface
    SDL_UpdateWindowSurface(window);
  }

  // Close SDL
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

