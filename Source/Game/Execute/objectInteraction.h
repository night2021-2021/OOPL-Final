#pragma once
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include "../mygame.h"
#include <vector>

namespace game_framework 
{
	class ObjectInteraction{

    public:
    
        void PerformAttacks(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies);


    private:

        bool IsWithinRange(const Operator* op, const Enemy* enemy);

        int CalculateDamage(const Operator* op, const Enemy* enemy);

    };

}