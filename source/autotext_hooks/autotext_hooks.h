#pragma once


#ifdef DLL_BUILD
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif


#define DLL_CALL _cdecl


namespace autotext_hooks 
{

DLL_DECL
bool 
DLL_CALL
installHooks();


DLL_DECL
bool
DLL_CALL
uninstallHooks();



}

