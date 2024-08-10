#pragma once
#include "../pch.h"
#include "../vector/vector.h"
#include "../globals/globals.h"
#include "../Entity/entity.h"

class Entity;

namespace Hacks {

	//module handle retreves a module handle for a specified module if the module is loaded in the calling process
	inline uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(L"sauerbraten.exe"));//gets the specified module base address
	inline Entity* localPlayer = *reinterpret_cast<Entity**>(baseModule + 0x2A2560);//Definition
	inline uintptr_t* entityList = *reinterpret_cast<uintptr_t**>(baseModule + 0x346C90);// sauerbraten.exe+346C90

	//Find the closest Entity
	Entity* closestEntity();

	//Check whether a key is pressed and to execute a function
	void checkHack();
	void aimbot();
	void noRecoil();
}
