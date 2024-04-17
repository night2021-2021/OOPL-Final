#pragma once
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include <memory>
#include <vector>

namespace game_framework 
{
	class ObjectInteraction{

    public:
    
        void AttackPerform(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies, float deltaTime, CheckpointManager& checkpointManager);


    private:

        bool RangeCheck(const Operator* op, const Enemy* enemy);

        int DamageCount(const Operator* op, const Enemy* enemy);

        void DamagePerform(int damage, Enemy* enemy, CheckpointManager& checkpointManager);

    };
}