#pragma once

#include "common.h"

// LOGGING TO USB

#include <fxlibc/printf.h>
#include <stdio.h>
#include <string.h>

#include <gint/usb.h>
#include <gint/usb-ff-bulk.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Globally changable text output buffer
extern char usb_text_buf[128];

#ifdef USB_LOGGING
void usblog(char const *file, char const *function, const char* fmt, ...);

#define LOG(FMT, ...) \
    usblog(__FILENAME__, __func__, FMT, ## __VA_ARGS__)

#else   // USB_LOGGING not def
#define LOG(FMT, ...)
#endif  // USB_LOGGING

#ifdef LOG_LEVEL_TRACE
#define LOG_TR(FMT, ...) \
  LOG(FMT, ## __VA_ARGS__)
#else
#define LOG_TR(FMT, ...)
#endif

#ifdef LOG_LEVEL_DEBUG
#define LOG_DEBUG(FMT, ...) \
  LOG(FMT, ## __VA_ARGS__)
#else
#define LOG_DEBUG(FMT, ...)
#endif

