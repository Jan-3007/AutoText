#pragma once


#ifdef DLL_BUILD
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

#define DLL_CALL _cdecl






namespace autotext_hooks 
{

typedef
void
DLL_CALL
KeystrokeCallback(
    void* context,
    WPARAM wParam, 
    LPARAM lParam
    );


DLL_DECL
bool 
DLL_CALL
installHooks(
    KeystrokeCallback* callback,
    void* context
    );


DLL_DECL
bool
DLL_CALL
uninstallHooks();



}

