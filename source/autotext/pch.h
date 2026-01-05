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


// JSON library, see https://github.com/nlohmann/json

// It's recommended to NOT USE implicit conversions from a JSON value, see 
// https://github.com/nlohmann/json?tab=readme-ov-file#implicit-conversions
#define JSON_USE_IMPLICIT_CONVERSIONS   0

#include "json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

