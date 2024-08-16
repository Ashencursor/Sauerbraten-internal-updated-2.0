#include "hacks.h"
#include "../pch.h"
#include <numbers>

namespace Hacks {

	//Find the closest Entity
	Entity& closestEntity() {
		auto closestEnt = *reinterpret_cast<Entity*>(entityList[1]);
		auto closestDist = FLT_MAX; // Initialize with max float value
		
		for (int i = 0; i < 32; i++) {
			auto entity = *reinterpret_cast<Entity*>(entityList[i]);

			if (!entity || &entity == localPlayer)
				continue;

			float distance = localPlayer->position.distance(entity.position);
			if (distance < closestDist) {
				closestDist = distance;
				//closestEnt = entity;
			}
		}
		return closestEnt;
	}


	void aimbot() {
		auto& closest_entity = closestEntity();
		Vector3 delta = localPlayer->getDelta(closest_entity);

		//This causes crash atm
		if (localPlayer) {
			//Calculate yaw
			float _yaw = std::atan2f(delta.y, delta.x) * (180.0 / std::numbers::pi_v<float>);
			localPlayer->yaw = _yaw + 270;

			//Calculate pitch
			float hypotenuse = std::hypot(delta.x, delta.y);
			float _pitch = std::atan2f(delta.z, hypotenuse) * (180.0 / std::numbers::pi_v<float>);
			
			//clamp
			if (_pitch < -90.0f) {
				_pitch = -90.0f;
			}
			else if (_pitch >= 90.0f) {
				_pitch = 90.0f;
			}

			if (_yaw >= 360.0f) {
				_yaw -= 360.0f;
			}
			else if (_yaw < 0.0f) {
				_yaw += 360.0f;
			}


			localPlayer->pitch = _pitch;
			localPlayer->yaw = _yaw + 270;
		}

		Sleep(1);
	}
}