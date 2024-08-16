#include "entity.h"



Vector3 Entity::getDelta(const Entity& entity) const
{
	return entity.position - Hacks::localPlayer->position;
}
