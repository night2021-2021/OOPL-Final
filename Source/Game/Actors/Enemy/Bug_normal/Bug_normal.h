#pragma once

#include "../Game/Actors/Character/mygame_enemy.h"

namespace game_framework
{
	class Bug_normal : public Enemy
	{
	public:
		Bug_normal()
			: Enemy(100, 100, 100, 1.5, 1) {}
	};
}