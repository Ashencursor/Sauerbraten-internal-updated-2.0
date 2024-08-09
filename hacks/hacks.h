#pragma once
#include "../pch.h"
#include "../Error/error.h"
#include "../vector/vector.h"
#include "../globals/globals.h"
#include "../Entity/entity.h"

namespace Hacks {

	//module handle retreves a module handle for a specified module if the module is loaded in the calling process
	inline uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(L"sauerbraten.exe"));//gets the specified module base address
	extern Entity* localPlayer;
	inline uintptr_t* entityList = *reinterpret_cast<uintptr_t**>(baseModule + 0x346C90);// sauerbraten.exe+346C90

	//Find the closest Entity
	Entity* closestEntity();

	//Check whether a key is pressed and to execute a function
	void checkHack();
	void aimbot(Entity entity);
	void noRecoil();
}
