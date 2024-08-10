#include "../pch.h"
#include "hacks.h"
#include "../hook/hook.h"

namespace Hacks {

	Entity* localPlayer = *reinterpret_cast<Entity**>(baseModule + 0x2A2560);//Definition


	//Find the closest Entity
	Entity* closestEntity() {
		Entity* closestEnt = nullptr;
		float closestDist = FLT_MAX;
		
		for (int i = 0; i < 31; i++) {
			Entity* entity = reinterpret_cast<Entity*>(entityList[i]);
			if (!entity)
				continue;
			if (entity->team == Hacks::localPlayer->team)
				continue;
			if (entity == Hacks::localPlayer)
				continue;
			
			float distance = localPlayer->position.distance(entity->position);
			if (distance < closestDist) {
				closestDist = distance;
				closestEnt = entity;
			}
		}
		//std::cout << closestEnt; This causes a crash
		return closestEnt;
	}

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

	void aimbot() {
		Entity* closest_entity = closestEntity();
		Vector3 delta = Hacks::localPlayer->getDelta(closest_entity);


	}
	void noRecoil() {

	}
}
