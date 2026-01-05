#pragma once

#include <filesystem>

#include "utils.h"



// keyword and its text expansion
struct Keyword
{
    std::string keyword;
    std::string snippet;
    std::filesystem::path file;

    // ctor
    Keyword(const std::string& kw)
        : keyword{kw}
        { }
};

using KeywordPtr = std::shared_ptr<Keyword>;


// list of keyword definitions
struct KeywordList
{
    std::string name;
    std::vector<KeywordPtr> keywords;

    // ctor
    KeywordList(const std::string& nm, const std::vector<KeywordPtr>& kw)
        : name{nm}, keywords{kw}
        { }
};

using KeywordListPtr = std::shared_ptr<KeywordList>;


// keywords associated with one program context
struct Program
{
    std::string name;
    std::vector<KeywordListPtr> keywordLists;

    // ctor
    Program(const std::string& nm, const std::vector<KeywordListPtr>& kwl)
        : name{nm}, keywordLists{kwl}
        { }
};

using ProgramPtr = std::shared_ptr<Program>;


// keywords that apply to global context (all programs)
struct Global
{
    std::vector<KeywordListPtr> keywordLists;

    // ctor
    Global(const std::vector<KeywordListPtr>& kwl)
        : keywordLists{kwl}
        { }
};

using GlobalPtr = std::shared_ptr<Global>;



class KeywordManager
{
public:

    // ctor
    KeywordManager();

    // dtor
    ~KeywordManager();


    // config files
    inline static const char filenameKeywords[] = "keywords.json";
    inline static const char filenamePrograms[] = "programs.json";

    // keys
    inline static const char keyKeyword[] = "keyword";
    inline static const char keySnippet[] = "snippet";
    inline static const char keyFile[] = "file";
    inline static const char keyName[] = "name";
    inline static const char keyKeywordLists[] = "keywordLists";
    inline static const char keyGlobal[] = "global";
    inline static const char keyPrograms[] = "programs";


    Status
    load(const std::filesystem::path& configDirectory);


    // returns nullptr if not found
    KeywordListPtr
    findKeywordList(std::string_view name);


private:

    Status
    loadKeywords(const std::filesystem::path& configDirectory);

    Status
    loadPrograms(const std::filesystem::path& configDirectory);

    void
    readKeywordsJson(const json& jsonObject);

    void
    readProgramsJson(const json& jsonObject);

    std::vector<KeywordPtr>
    readKeywordsArray(const json& jsonArray);

    std::vector<KeywordListPtr>
    readKeywordListsAttribute(const json& jsonObject);

    std::vector<ProgramPtr>
    readProgramsArray(const json& jsonArray);


private:
    
    std::vector<KeywordListPtr> mAllKeywordLists;
    std::vector<ProgramPtr> mProgramList;
    GlobalPtr mGlobal;
};

