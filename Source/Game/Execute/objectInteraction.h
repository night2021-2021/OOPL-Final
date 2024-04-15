#pragma once
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include "../mygame.h"
#include <vector>

namespace game_framework 
{
	class ObjectInteraction{

    public:
    
        void AttackPerform(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies);


    private:

        bool RangeCheck(const Operator* op, const Enemy* enemy);

        int DamageCount(const Operator* op, const Enemy* enemy);

    };
}