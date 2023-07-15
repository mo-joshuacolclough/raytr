#pragma once

// LOGGING TO USB

// Trace prints?
//#define LOG_LEVEL_TRACE
// Debug prints?
#define LOG_LEVEL_DEBUG

#include <fxlibc/printf.h>
#include <stdio.h>
#include <string.h>

#include <gint/usb.h>
#include <gint/usb-ff-bulk.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Globally changable text output buffer
extern char usb_text_buf[1024];

void usblog(char const *file, char const *function, const char* fmt, ...);

#define LOG(FMT, ...) \
    usblog(__FILENAME__, __func__, FMT, ## __VA_ARGS__)

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


