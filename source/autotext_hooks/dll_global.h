#pragma once



#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files
#include <windows.h>



// Logging library, see https://github.com/gabime/spdlog

// use C++20 std::format
#define SPDLOG_USE_STD_FORMAT

// define log level
#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#endif


#include "spdlog/spdlog.h"

// use Windows debug sink (logging using OutputDebugStringA):
#include "spdlog/sinks/msvc_sink.h"



extern HMODULE gDllModuleHandle;