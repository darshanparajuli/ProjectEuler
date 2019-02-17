#ifndef PE_LOG_H
#define PE_LOG_H

#include "types.h"

#define LOG(tag, ...) _log((tag), __VA_ARGS__)
#define LOGI(...) _log(" INFO", __VA_ARGS__)
#define LOGD(...) _log("DEBUG", __VA_ARGS__)
#define LOGE(...) _log("ERROR", __VA_ARGS__)

void _log(cstr *tag, cstr *format, ...);

#endif
