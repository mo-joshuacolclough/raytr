#include "log.h"

void usblog(char const *file, char const *function, const char* fmt, ...) {
  sprintf(usb_text_buf, "%s:%s: ", file, function);

  va_list args;
  va_start(args, fmt);
  vsprintf(usb_text_buf + strlen(usb_text_buf), fmt, args);
  va_end(args);

  // Flush to USB
  usb_fxlink_text(usb_text_buf, 0);
}
