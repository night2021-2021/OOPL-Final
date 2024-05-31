#pragma once
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include <memory>
#include <vector>

namespace game_framework 
{
	class ObjectInteraction{

    public:
    
        void OperatorAttackPerform(std::vector<std::unique_ptr<Operator>>& operators, std::vector<std::shared_ptr<Enemy>>& enemies, float deltaTime, CheckpointManager& checkpointManager);

        void OperatorHealPerform(std::vector<std::unique_ptr<Operator>>& operators, std::vector<std::unique_ptr<Operator>>& allies, float deltaTime, CheckpointManager& checkpointManager);

        void EnemyAttackPerform(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Operator>>& operators, float deltaTime, CheckpointManager& checkpointManager);

    private:
        bool OperatorRangeCheck(const Operator* op, const Enemy* enemy);

        int OperatorDamageCount(const Operator* op, const Enemy* enemy);
        
        void OperatorDamagePerform(int damage, Enemy* enemy, CheckpointManager& checkpointManager);

        bool HealerRangeCheck(const Operator* op, const Operator* allies);

        int OperatorHealCount(const Operator* op, const Operator* targetOp);

        void OperatorRecoverPerform(int heal, Operator* targetOp);

        bool EnemyRangeCheck(const Operator* op, const Enemy* enemy);

        int EnemyDamageCount(const Operator* op, const Enemy* enemy);

        void EnemyDamagePerform(int damage, Operator* op, CheckpointManager& checkpointManager);
    };
}