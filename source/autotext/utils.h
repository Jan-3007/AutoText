#pragma once


//
// Convert (cast) an enum value to its underlying type.
//
template <typename E>
constexpr
auto
toUnderlyingType(E enumValue)
{
    static_assert(std::is_enum<E>::value, "Argument must be an enum type.");

    return static_cast<typename std::underlying_type<E>::type>(enumValue);
}


//
// custom status codes for AutoText
//
enum class Status : int
{
    Success = 0,
    FileOpenFailed,
    JsonError,
};


//
// custom logging formatter for Status
//
template<>
struct std::formatter<Status> : std::formatter<int>
{
    auto format(Status st, format_context& ctx) const -> decltype(ctx.out())
    {
        return std::formatter<int>::format(toUnderlyingType(st), ctx);
    }
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



