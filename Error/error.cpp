#include "../pch.h"
#include "error.h"

namespace Check
{
	bool isPlayerValid(Entity* entity)
	{
		if (entity == nullptr)
			return false;
		if (entity == Hacks::localPlayer)
			return false;
		//Check isAlive
		if (!entity->isAlive && entity->displayHealth < 1000 && entity->displayHealth > 0) {
			return false;
		}
		return true;
	}
	bool isGood(Entity* entity)
	{
		return std::string_view{ entity->team, 4 } == "good";
	}
	bool isEvil(Entity* entity)
	{
		return std::string_view{ entity->team, 4 } == "evil";
	}
}