#pragma once


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
        return std::formatter<int>::format(stdx::to_underlying_type(st), ctx);
    }
};

