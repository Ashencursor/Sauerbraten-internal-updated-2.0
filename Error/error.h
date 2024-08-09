#pragma once
#include "../pch.h"
#include "../hacks/hacks.h"
#include "../Entity/entity.h"

namespace Check
{
	bool isPlayerValid(Entity* entity);
	bool isGood(Entity* entity);
	bool isEvil(Entity* entity);
}