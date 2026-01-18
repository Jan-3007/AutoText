

#include "dll_global.h"
#include "autotext_hooks.h"




namespace autotext_hooks
{

HHOOK gHookHandle = nullptr;


LRESULT
CALLBACK
keyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)	{

		SPDLOG_DEBUG("nCode={}, wParam={:#x}, lParam={:#x}", nCode, wParam, lParam);

	}

	return CallNextHookEx(gHookHandle, nCode, wParam, lParam);
}




__declspec(dllexport)
bool
installHooks()
{
	if (gHookHandle != nullptr)	{
		SPDLOG_ERROR("hook already installed");
		return false;
	}

	gHookHandle = ::SetWindowsHookEx(
		WH_KEYBOARD,					//[in] int       idHook,
		keyboardHookCallback,			//[in] HOOKPROC  lpfn,
		gDllModuleHandle,				//[in] HINSTANCE hmod,
		0								//[in] DWORD     dwThreadId
		);

	if (gHookHandle == nullptr)	{
		DWORD err = ::GetLastError();
		SPDLOG_ERROR("SetWindowsHookExW() failed, err={}", err);
		return false;
	}

	SPDLOG_INFO("hook successfully installed, gDllModuleHandle={}", static_cast<void*>(gDllModuleHandle));
	return true;
}


__declspec(dllexport)
bool
uninstallHooks()
{
	if (gHookHandle != nullptr)	{
		BOOL succ = UnhookWindowsHookEx(gHookHandle);

		if (!succ) {
			DWORD err = ::GetLastError();
			SPDLOG_ERROR("UnhookWindowsHookEx() failed, err={}", err);
			return false;
		}
	}

	return true;
}





}