#pragma once

#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files
#include <windows.h>

// C++ RunTime Header Files
#include <string>
#include <memory>
#include <utility>
#include <stdexcept>
#include <type_traits>



// our std extension library

#include "libstdx.h"





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





// JSON library, see https://github.com/nlohmann/json

// It's recommended to NOT USE implicit conversions from a JSON value, see 
// https://github.com/nlohmann/json?tab=readme-ov-file#implicit-conversions
#define JSON_USE_IMPLICIT_CONVERSIONS   0

#include "nlohmann/json.hpp"

using json = nlohmann::json;




