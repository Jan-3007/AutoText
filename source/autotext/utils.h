#pragma once


enum class Status
{
    Success = 0,
    FileOpenFailed,
    JsonError,


};




//
// Convert all characters to lower case.
//
template <typename CharT> // char, wchar_t
std::basic_string<CharT>
convertStringToLowerCase(std::basic_string_view<CharT> str)
{
    std::basic_string<CharT> newStr;
    newStr.reserve(str.size());

    for ( CharT c : str ) {
        newStr += static_cast<CharT>(std::tolower(c));
    }

    return newStr;
}

