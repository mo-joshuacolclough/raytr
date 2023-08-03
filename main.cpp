#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <fstream>
#include <chrono>

#include <SDL2/SDL.h>

#include "common.h"
#include "camera.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "body.h"
#include "sphere.h"
#include "light.h"
#include "ground.h"
#include "world.h"
#include "plane.h"

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
    const Vec3 hitpos = r.at(t);
    Color final_col = hitobj->color_at(hitpos) * last_col;
    const Vec3 hitnorm = hitobj->normal_at(hitpos);

    // For each light, combine color
    // also check if light is blocked by another object
    const float numLightf = static_cast<float>(world.lights.size());
    for (const Light& l : world.lights) {
      // Get direction to light from hit pos
      const Vec3 dir = l.pos - hitpos;
      const Vec3 dir_unit = unit_vector(dir);

#ifdef SHADOWS
      Ray shadowray = Ray(hitpos, dir_unit);
      for (const std::shared_ptr<Body>& b : world.bodies) {
        final_col *= !(b->id != hitobj->id && b->hit(shadowray) > 0.0);
        //if (b->id != hitobj->id && b->hit(shadowray) > 0.0) {
        //  return Color(0.0, 0.0, 0.0);
        //}
      }
#endif  // SHADOWS

      // dot product with normal = lighting
      float d = dot(unit_vector(dir), hitnorm);
      d = d < 0.0 ? 0.0 : d;
      final_col[0] *= l.col[0] * d / numLightf;
      final_col[1] *= l.col[1] * d / numLightf;
      final_col[2] *= l.col[2] * d / numLightf;
    }

#ifdef REFLECTIONS
    // Reflect and call again
    if (depth < MAX_REFLECTIONS && hitobj->reflectivity > 0.001) {
      const Ray reflected = r.reflect(hitnorm, hitpos, hitobj->reflectivity);
      final_col = ray_color(reflected, world, final_col, depth+1);
    }
#endif  // REFLECTIONS

    return final_col * r.getBrightness();
  }

  t = 0.5 * (r.direction().y() + 1.0);
  return last_col * ((1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0));
}

namespace {

inline Uint32 to_pixel(SDL_Surface* surface, const Color& color) {
  return SDL_MapRGBA(surface->format,
                     static_cast<uint8_t>(color[0] * 255),
                     static_cast<uint8_t>(color[1] * 255),
                     static_cast<uint8_t>(color[2] * 255),
                     255);
}

}  // namespace


int main() {
  // Following https://raytracing.github.io/books/RayTracingInOneWeekend.html
  SDL_Window* window = nullptr;
  SDL_Surface* screen_surface = nullptr;
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Raytr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  screen_surface = SDL_GetWindowSurface(window);

  // Scene
  World world = World();
  Camera camera;
  camera.calculate_ray_directions();

  bool quit = false;
  float a = 0.0;

  // Time
  typedef std::chrono::high_resolution_clock Clock;
  Clock::time_point time_now = Clock::now();
  Clock::time_point time_last;

  //Event handler
  SDL_Event event;
  
  #pragma omp parallel
  #pragma omp master
  {
    while(!quit) {
      time_last = time_now;
      time_now = Clock::now();
      std::chrono::duration<float> dt_duration = time_now - time_last;
      float dt = dt_duration.count();
      std::cout << "FPS: " << 1.0/dt << std::endl;

      // Keyboard
      while(SDL_PollEvent(&event) != 0) {
        quit = quit | (event.type == SDL_QUIT);
        camera.handle_event(event);
      }

      // Update
      a += 10.0 * dt;
      world.bodies[0]->pos.y() = (std::sin(a) / 4.0) + 0.25;

      camera.update(dt);
      
      // Draw

      // Lock screen image
      SDL_LockSurface(screen_surface);
      Uint32* buffer = static_cast<Uint32*>(screen_surface->pixels);

      #pragma omp taskloop grainsize(DEF_SCREEN_WIDTH)
      for (size_t idx = 0; idx < SCREEN_WIDTH * SCREEN_HEIGHT; ++idx) {
        const Color ray_color_out = ray_color(camera.make_ray(idx), world, Color(1.0, 1.0, 1.0), 0);
        buffer[idx] = to_pixel(screen_surface, ray_color_out);
      }

      #pragma omp taskwait
      SDL_UnlockSurface(screen_surface);
      SDL_UpdateWindowSurface(window);
    }

  }  // omp

  // Close SDL
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

