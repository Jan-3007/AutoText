#pragma once

#include <cstdio>

#include "utils.h"



class File
{
public:

    // ctor
    File();

    // dtor
    ~File();


    Status
    open(const char* filename, const char* mode);

    void
    close();


    std::FILE*
    getFilePtr() const
        { return mFile; }

private:
    std::FILE* mFile {nullptr};
};

