#include "pch.h"

#include "File.h"


// ctor
File::File()
{
}

// dtor
File::~File()
{
    close();
}


Status
File::open(const char* filename, const char* mode)
{
    close();

    mFile = std::fopen(filename, mode);
    if ( !mFile ) {
        return Status::FileOpenFailed;
    }

    return Status::Success;
}


void
File::close()
{
    if ( mFile ) {
        std::fclose(mFile);
        mFile = nullptr;
    }
}

