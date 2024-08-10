#include "entity.h"


bool Entity::isValid()
{
	if (this == nullptr)
		return false;
	if (this == Hacks::localPlayer)
		return false;
	//Check isAlive
	if (!isAlive && displayHealth < 1000 && displayHealth > 0) {
		return false;
	}
	return true;
}

bool Entity::isGood()
{
	return std::string_view{ team, 4 } == "good";
}

bool Entity::isEvil()
{
	return std::string_view{ team, 4 } == "evil";
}

Vector3 Entity::getDelta(Entity* entity)
{
	return entity->position - Hacks::localPlayer->position;
}
