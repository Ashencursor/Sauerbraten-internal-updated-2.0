#include "../pch.h"
#include "hacks.h"


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
			float distance = localPlayer->position.distance(entity->position);
			if (distance < closestDist) {
				closestDist = distance;
				closestEnt = entity;
			}
		}
		return closestEnt;
	}

	//Check whether a key is pressed and to execute a function
	void checkHack() {
		//Testing
		if (GetAsyncKeyState(VK_F2) & 1) {
			toggles::rapidFire = !toggles::rapidFire;
			Sleep(1);//Prevent GetAsyncKeyState to be called multiple times and run twice
		}
		//In developement
		if (GetAsyncKeyState(VK_F3) & 1) {
			toggles::noRecoil = !toggles::noRecoil;
			Sleep(1);
		}
		if (GetAsyncKeyState(VK_F4) & 1) {
			toggles::aimbot = !toggles::aimbot;
			Sleep(1);
		}
	}

	void aimbot(Entity entity) {

	}
	void noRecoil() {

	}
}
