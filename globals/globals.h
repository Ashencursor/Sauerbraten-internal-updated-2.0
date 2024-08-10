#pragma once
#include "../pch.h"

namespace Globals
{
	//Things to toggle for hack
	inline bool gui = false;
	inline bool rapidFire = false; // Still testing out(odd how it works)
	inline bool isHooked = false;
	inline bool noRecoil = false;
	inline bool aimbot = false;

	//hooking
	namespace Hook {
		inline HMODULE Opengl = GetModuleHandle(L"opengl32.dll");
		inline uintptr_t swapBuffersPtr =
			reinterpret_cast<uintptr_t>(GetProcAddress(Opengl, "wglSwapBuffers"));
	}
}
