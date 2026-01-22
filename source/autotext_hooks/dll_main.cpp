
#include "dll_global.h"



// module handle of DLL as passed to DllMain
HMODULE gDllModuleHandle = nullptr;


//
// DLL Main Entry Point
//
BOOL
APIENTRY
DllMain(
    HMODULE hModule,
    DWORD  dwReason,
    LPVOID lpReserved
    )
{

    switch (dwReason) {

        case DLL_PROCESS_ATTACH:
            // save module handle
            gDllModuleHandle = hModule;

            // configure spdlog
            {
                // set check_debugger_present = false
                auto sink = std::make_shared<spdlog::sinks::msvc_sink_st>(false);
                sink->set_pattern("%T.%e AutoTextDLL [%P] (%t) [%l] %!: %v");

                auto logger = std::make_shared<spdlog::logger>("AutoText", sink);
                spdlog::set_default_logger(logger);
                spdlog::set_level(spdlog::level::trace);
            }

            SPDLOG_INFO("Initialized logging for DLL");

            SPDLOG_INFO("DLL_PROCESS_ATTACH lpReserved={} ({})", lpReserved, (nullptr == lpReserved) ? "LoadLibrary" : "static load");
            break;

        case DLL_PROCESS_DETACH:
            SPDLOG_INFO("DLL_PROCESS_DETACH lpReserved={} ({})", lpReserved, (nullptr == lpReserved) ? "FreeLibrary" : "process terminating");
            break;

        case DLL_THREAD_ATTACH:
            SPDLOG_INFO("DLL_THREAD_ATTACH");
            break;

        case DLL_THREAD_DETACH:
            SPDLOG_INFO("DLL_THREAD_DETACH");
            break;

        default:
            SPDLOG_INFO("dwReason={}", dwReason);
            break;

    }//switch

    return TRUE;

}//DllMain