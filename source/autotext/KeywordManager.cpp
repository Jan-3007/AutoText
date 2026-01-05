#include "pch.h"

#include "KeywordManager.h"
#include "File.h"


// ctor
KeywordManager::KeywordManager()
{
}

// dtor
KeywordManager::~KeywordManager()
{
}


Status
KeywordManager::load(const std::filesystem::path& configDirectory)
{


    return Status::Success;
}


KeywordListPtr 
KeywordManager::findKeywordList(std::string_view name)
{
    for ( const auto& kwl : mAllKeywordLists ) {
        // case-sensitive string compare
        if ( kwl->name == name ) {
            return kwl;
        }
    }

    return nullptr;
}


Status
KeywordManager::loadKeywords(const std::filesystem::path& configDirectory)
{
    std::filesystem::path filePath = configDirectory / filenameKeywords;

    // try to open the file - binary mode (no CR/LF conversion)
    File f;
    Status st = f.open(filePath.string().c_str(), "rb");
    if ( st != Status::Success ) {
        //TODO error logging
        return st;
    }

    // parse JSON text
    try {

        json data = json::parse(f.getFilePtr());

        readKeywordsJson(data);

    } catch (const json::exception& ex) {
        //TODO error logging
        return Status::JsonError;

    } catch (const std::exception& ex) {
        //TODO error logging
        return Status::JsonError;
    }

    return Status::Success;
}


Status 
KeywordManager::loadPrograms(const std::filesystem::path& configDirectory)
{
    std::filesystem::path filePath = configDirectory / filenamePrograms;

    // try to open the file - binary mode (no CR/LF conversion)
    File f;
    Status st = f.open(filePath.string().c_str(), "rb");
    if ( st != Status::Success ) {
        //TODO error logging
        return st;
    }

    // parse JSON text
    try {

        json data = json::parse(f.getFilePtr());

        readProgramsJson(data);

    } catch (const json::exception& ex) {
        //TODO error logging
        return Status::JsonError;

    } catch (const std::exception& ex) {
        //TODO error logging
        return Status::JsonError;
    }

    return Status::Success;
}


void
KeywordManager::readKeywordsJson(const json& jsonObject)
{
    // iterate elements in the top level object
    for ( const auto& element : jsonObject.items() ) {

        // value is expected to be an array
        json array = element.value();
        if ( !array.is_array() ) {
            //TODO error logging

            // skip this element
            continue;
        }

        // each element represents a list of keywords
        KeywordListPtr keywordList = std::make_shared<KeywordList>(
                                            element.key(),
                                            readKeywordsArray(array)
                                            );
        // store
        mAllKeywordLists.push_back(keywordList);
    }
}


std::vector<KeywordPtr>
KeywordManager::readKeywordsArray(const json& jsonArray)
{   
    std::vector<KeywordPtr> keywords;
    
    // iterate array
    for ( const auto& object : jsonArray ) {

        // each item is expected to be an object (dict)
        if ( !object.is_object() ) {
            //TODO error logging
            // skip this element
            continue;
        }

        // keyword is mandatory
        if ( !object.contains(keyKeyword) ) {
            //TODO error logging
            // skip this element
            continue;
        }

        KeywordPtr keyword = std::make_shared<Keyword>(
                                    object.at(keyKeyword).get<std::string>()
                                    );

        // snippet is optional
        if ( object.contains(keySnippet) ) {
            keyword->snippet = object.at(keySnippet).get<std::string>();
        }

        // file is optional
        if ( object.contains(keyFile) ) {
            keyword->file = object.at(keyFile).get<std::string>();
        }

        // store
        keywords.push_back(keyword);
    }

    return keywords;
}


void
KeywordManager::readProgramsJson(const json& jsonObject)
{
    // global is optional
    if ( jsonObject.contains(keyGlobal) ) {
        mGlobal = std::make_shared<Global>(
                        readKeywordListsAttribute(jsonObject.at(keyGlobal))
                        );
    }

    // programs is optional
    if ( jsonObject.contains(keyPrograms) ) {
        // and is expecteted to be an array
        json array = jsonObject.at(keyPrograms);
        if ( !array.is_array() ) {
            //TODO error logging
        } else {
            mProgramList = readProgramsArray(array);
        }
    }
}


std::vector<ProgramPtr>
KeywordManager::readProgramsArray(const json& jsonArray)
{
    std::vector<ProgramPtr> programs;

    // iterate array
    for ( const auto& object : jsonArray ) {

        // each item is expected to be an object (dict)
        if ( !object.is_object() ) {
            //TODO error logging
            // skip this element
            continue;
        }

        // name is mandatory
        if ( !object.contains(keyName) ) {
            //TODO error logging
            // skip this element
            continue;
        }

        json name = object.at(keyName);

        // name must be a string
        if ( !name.is_string() ) {
            //TODO error logging
            // skip this element
            continue;
        }

        ProgramPtr prog = std::make_shared<Program>(
                                    name.get<std::string>(),
                                    readKeywordListsAttribute(object)
                                    );
        programs.push_back(prog);
    }

    return programs;
}


std::vector<KeywordListPtr>
KeywordManager::readKeywordListsAttribute(const json& jsonObject)
{
    // keywordLists is optional, list is empty by default
    if ( !jsonObject.contains(keyKeywordLists) ) {
        return std::vector<KeywordListPtr> {};
    }

    json array = jsonObject.at(keyKeywordLists);
        
    // keywordLists is expected to be an array
    if ( !array.is_array() ) {
        //TODO error logging
        return std::vector<KeywordListPtr> {};
    }

    std::vector<KeywordListPtr> keywordLists;

    // iterate array
    for ( const auto& item : array ) {
        
        // each item is expected to be a string
        if ( !item.is_string() ) {
            //TODO error logging
            // skip
            continue;
        }

        auto listName = item.get<std::string>();

        KeywordListPtr list = findKeywordList(listName);
        if ( !list ) {
            //TODO error logging
            // list not defined, skip
            continue;
        }
        
        keywordLists.push_back(list);
    }

    return keywordLists;
}

