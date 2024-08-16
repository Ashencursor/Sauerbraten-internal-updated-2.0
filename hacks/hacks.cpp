#include "../pch.h"
#include "hacks.h"
#include "../hook/hook.h"

#include <limits>
#include <numbers>

namespace Hacks {

	//Check whether a key is pressed and to execute a function
	void checkHack() {
		//Testing
		if (GetAsyncKeyState(VK_F2) & 1) {
			Globals::rapidFire = !Globals::rapidFire;
			Sleep(1);//Prevent GetAsyncKeyState to be called multiple times and run twice
		}
		//In developement
		if (GetAsyncKeyState(VK_F3) & 1) {
			Globals::noRecoil = !Globals::noRecoil;
			Sleep(1);
		}
		if (GetAsyncKeyState(VK_F4) & 1) {
			Globals::aimbot = !Globals::aimbot;
			Sleep(1);
		}
		if (Globals::aimbot) {
			aimbot();
		}
		if (GetAsyncKeyState(VK_F5) & 1) {
			Globals::isHooked = Globals::isHooked;
			if (Globals::isHooked) {
				//Hook::unhook(reinterpret_cast<uintptr_t>(&test));
			}
			Sleep(1);
		}
	}
}
