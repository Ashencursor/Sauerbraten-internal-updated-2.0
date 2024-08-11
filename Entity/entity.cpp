#include "entity.h"


bool Entity::isGood()
{
	return std::string_view{ team, 4 } == "good";
}

bool Entity::isEvil()
{
	return std::string_view{ team, 4 } == "evil";
}

Vector3 Entity::getDelta(Entity& entity)
{
	return entity.position - Hacks::localPlayer->position;
}
