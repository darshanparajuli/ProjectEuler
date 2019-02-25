#ifndef PE_LOG_H
#define PE_LOG_H

#include "types.h"

#define _RED_COLOR "\033[0;31m"
#define _NO_COLOR "\033[0m"

#define LOG(tag, ...) _log((tag), _NO_COLOR, __VA_ARGS__)
#define LOGI(...) _log(" INFO", _NO_COLOR, __VA_ARGS__)
#define LOGD(...) _log("DEBUG", _NO_COLOR, __VA_ARGS__)
#define LOGE(...) _log("ERROR", _RED_COLOR, __VA_ARGS__)

void _log(cstr *tag, cstr *colorCode, cstr *format, ...);

#endif
