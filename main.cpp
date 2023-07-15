#include <cmath>
#include <memory>

#include <gint/clock.h>
#include <gint/display.h>
#include <gint/keycodes.h>
#include <gint/keyboard.h>
#include <gint/usb.h>
#include <gint/usb-ff-bulk.h>

#include <fxlibc/printf.h>
#include <stdio.h>
#include <cstring>

#include "common.h"
#include "log.h"
#include "vec3.h"
#include "camera.h"
#include "color.h"
#include "ray.h"
#include "body.h"
#include "sphere.h"
#include "light.h"
#include "ground.h"
#include "world.h"
#include "plane.h"

// Following https://raytracing.github.io/books/RayTracingInOneWeekend.html

namespace {

Color ray_color(Ray r, const World& world, Color last_col, unsigned int depth) {
  float t = -1.0; // position along ray of closest hit
  std::shared_ptr<Body> hitobj; // object that was hit

  for (const std::shared_ptr<Body>& b : world.bodies) {
    float dist = b->hit(r);

    // If it is the closest object
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
    // const float numLightf = static_cast<float>(world.lights.size());
    for (const Light& l : world.lights) {
      // Get direction to light from hit pos
      Vec3 dir_unit = l.pos - hitpos;
      dir_unit = unit_vector(dir_unit);

#ifdef SHADOWS
      Ray shadowray = Ray(hitpos, dir_unit);
      for (const std::shared_ptr<Body>& b : world.bodies) {
        if (b->id != hitobj->id) {
          float d = b->hit(shadowray);
          if (d > 0.0) return Color(0.0, 0.0, 0.0);
        }
      }
#endif  // SHADOWS

      // dot product with normal = lighting
      float d = dot(dir_unit, hitnorm);
      d *= d > 0.0;  // max(0.0, d)
      final_col[0] *= l.col[0] * d;
      final_col[1] *= l.col[1] * d;
      final_col[2] *= l.col[2] * d;
    }

#ifdef REFLECTIONS
    // Reflect and call again
    if (depth < MAX_REFLECT && hitobj->reflectivity != 0.0) {
      r.reflect(hitnorm, hitpos, hitobj->reflectivity);
      final_col = ray_color(r, world, final_col, depth+1);
    }
#endif  // REFLECTIONS

    // Vec3 n = unit_vector(r.at(t) - hitobj->pos);
    return final_col * r.getBrightness();
  }

  t = 0.5 * (r.direction().y() + 1.0);
  return last_col * ((1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.4, 0.7, 1.0));
}

}  // namespace

char usb_text_buf[128];

int main() {
#ifdef USB_LOGGING
  usb_interface_t const *interfaces[] = { &usb_ff_bulk, NULL };
  if (!usb_open(interfaces, GINT_CALL_NULL)) {
    usb_open_wait();
  }
#endif

  LOG("Starting...");
  LOG("Display size: %dx%d", DWIDTH, DHEIGHT);
  LOG("Resolution size: %dx%d", RAYX, RAYY);
  LOG("Total Vec3 bytes: %d", sizeof(Vec3) * RAYX * RAYY);

  // Scene
  World world = World();

  LOG("Setting up camera...");
  // Setup Camera
  Camera camera;
  camera.calculate_ray_directions();
  LOG("Camera setup done.");
  
  bool stop = false;
  bool keyboard_pressed = false;

  // OVERCLOCK
#ifdef OVERCLOCK
  clock_set_speed(CLOCK_SPEED_F4);
#endif

  float a = 0.0;
  Color pixel_color;

  while (!stop) {
    // Update
    if (keyboard_pressed)
      keyboard_pressed = false;

    a += 0.5;
    world.bodies[0]->pos.y() = (sin(a) / 4.0) + 0.25;

    // Draw
    uint16_t p_idx, ray_idx;
    
    color_t pixel_color_t;
    for (uint16_t j = 0; j < RAYY; ++j) {
      for (uint16_t i = 0; i < RAYX; ++i) {
        ray_idx = (RAYY - j - 1) * RAYX + i;

        pixel_color_t = get_color_t(ray_color(camera.make_ray(ray_idx), world, Color(1.0, 1.0, 1.0), 0));
        
        // TEST SCREEN:
        //pixel_color_t = get_color_t(Color(a, a*a, a*a*a));

        drect(i * DEFINITION, j * DEFINITION, (i+1) * DEFINITION, (j+1) * DEFINITION, pixel_color_t);
      }
    }
    dupdate();

    // Keyboard events
    key_event_t key_press = pollevent();
    if (key_press.type != KEYEV_NONE &&
        (key_press.type == KEYEV_DOWN ||
         key_press.type == KEYEV_HOLD)) {
      switch (key_press.key) {
        case KEY_LEFT:
          camera.rotate_left();
          break;
        case KEY_RIGHT:
          camera.rotate_right();
          break;
        // -- Forward, back --
        case KEY_8:
          camera.move_forward();
          break;
        case KEY_5:
          camera.move_back();
          break;
        // -- Left, right --
        case KEY_4:
          camera.strafe_left();
          break;
        case KEY_6:
          camera.strafe_right();
          break;
        // -- Up, down --
        case KEY_9:
          camera.move_up();
          break;
        case KEY_7:
          camera.move_down();
          break;
        case KEY_EXIT:
          LOG("Exiting.");
          stop = true;
          break;
      }

      keyboard_pressed = true;
      clearevents();
    }
  }

#ifdef USB_LOGGING
  usb_close();
#endif

  return 0;
}
