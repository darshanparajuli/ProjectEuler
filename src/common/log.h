#ifndef PE_LOG_H
#define PE_LOG_H

#include "types.h"

#define _RED_COLOR "\033[0;31m"

#define LOG(tag, ...) _log((tag), "", __VA_ARGS__)
#define LOGI(...) _log(" INFO", "", __VA_ARGS__)
#define LOGD(...) _log("DEBUG", "", __VA_ARGS__)
#define LOGE(...) _log("ERROR", _RED_COLOR, __VA_ARGS__)

void _log(cstr *tag, cstr *colorCode, cstr *format, ...);

#endif
