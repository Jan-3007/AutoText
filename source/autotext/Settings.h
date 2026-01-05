#pragma once

#include <filesystem>

#include "utils.h"


class Settings
{
public:

    // ctor
    Settings();

    // dtor
    ~Settings();

    // path relative to %USERPROFILE%\Documents
    static constexpr std::wstring_view DefaultDocumentsPath = L"AutoText";

    // keys
    inline static const char keyTrigger[] = "trigger";
    inline static const char keyConfigDirectory[] = "configDirectory";



    Status
    load(const std::filesystem::path& filePath);


private:
    
    void
    readJson(const json& jsonObject);

    static
    bool
    checkTrigger(std::string_view trig);


private:

    // empty string means: no trigger, no text expansion will happen
    std::string mTrigger;

    // if not empty, overrules default directory
    std::filesystem::path mConfigDirectory;

};

