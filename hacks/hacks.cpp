#include "../pch.h"
#include "hacks.h"
#include "../hook/hook.h"

#include <limits>
#include <numbers>

namespace Hacks {

	//Find the closest Entity
	Entity& closestEntity() {
		auto& closestEnt = *reinterpret_cast<Entity*>(entityList[0]);
		auto closestDist = FLT_MAX; // Initialize with max float value

		for (int i = 0; i < 31; i++) {
				auto& entity = *reinterpret_cast<Entity*>(entityList[i]);
			if (!entity)
				continue;
			if (entity.team == localPlayer->team)
				continue;
			if (&entity == localPlayer)
				continue;

			float distance = localPlayer->position.distance(entity.position);
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
		auto& closest_entity = closestEntity();
		Vector3 delta = localPlayer->getDelta(closest_entity);

		//This causes crash atm
		if (localPlayer) {
			//Calculate yaw
			float _yaw = std::atan2f(delta.y, delta.x) * (180.0 / std::numbers::pi_v<float>) + 90;
			localPlayer->yaw = _yaw;

			//Calculate pitch
			float hypotenuse = std::hypot(delta.x, delta.y);
			float _pitch = std::atan2f(-delta.z, hypotenuse) * (180.0 / std::numbers::pi_v<float>);
			localPlayer->pitch = _pitch;
		}

		Sleep(1);
	}
	//Nop pitch
	void noRecoil() {

	}
}
