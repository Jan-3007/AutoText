#include "pch.h"

#include "Settings.h"
#include "File.h"


// ctor
Settings::Settings()
{
}

// dtor
Settings::~Settings()
{
}


Status 
Settings::load(const std::filesystem::path& filePath)
{
    // try to open the file - binary mode (no CR/LF conversion)
    File f;
    Status st = f.open(filePath.string().c_str(), "rb");
    if ( st != Status::Success ) {
        SPDLOG_ERROR("open({}) failed, st = {}", filePath.string(), st);
        return st;
    }

    // parse JSON text
    try {

        json data = json::parse(f.getFilePtr());

        readJson(data);

    } catch (const json::exception& ex) {
        SPDLOG_ERROR("json::exception: {}", ex.what());
        return Status::JsonError;

    } catch (const std::exception& ex) {
        SPDLOG_ERROR("std::exception: {}", ex.what());
        return Status::JsonError;
    }
    
    return Status::Success;
}


void
Settings::readJson(const json& jsonObject)
{
    // optional, no trigger by default
    if ( jsonObject.contains(keyTrigger) ) {
        auto trig = jsonObject.at(keyTrigger).get<std::string>();
        if ( checkTrigger(trig) ) {
            mTrigger = trig;
        }
    }

    // optional, use default path if not given or non-existing
    if ( jsonObject.contains(keyConfigDirectory) ) {
        auto cd = jsonObject.at(keyConfigDirectory).get<std::string>();
        std::filesystem::path dir {cd};
        if ( std::filesystem::is_directory(dir) ) {
            mConfigDirectory = dir;
        }
    }
}


//static
bool 
Settings::checkTrigger(std::string_view trig)
{
    std::string lcTrig = convertStringToLowerCase(trig);

    if ( lcTrig == "tab" ) {
        return true;
    }
    
    if ( lcTrig == "shift+tab" ) {
        return true;
    }

    if ( lcTrig == "alt+tab" ) {
        return true;
    }

    if ( lcTrig == "ctrl+tab" ) {
        return true;
    }

    return false;
}
