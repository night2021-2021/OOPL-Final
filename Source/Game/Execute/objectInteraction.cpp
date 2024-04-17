#include "StdAfx.h"
#include "objectInteraction.h"
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include <memory>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                  \
   OutputDebugString( os_.str().c_str() );  \
}	

namespace game_framework
{
    void ObjectInteraction::AttackPerform(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies, float deltaTime, CheckpointManager& checkpointManager) {
        for (auto& operatorPtr : operators) {
            if (!operatorPtr->isPlacing)
            {
				continue;
			}

            operatorPtr->attackCD += deltaTime;
            if (operatorPtr->attackCD >= operatorPtr->attackSpeed) {
                bool isAttack = false;                      //Once the operator attacks, the state will be changed to ATTACK    (Operator can cattack and only attack one enemy at same time.)
                for (auto& enemyPtr : enemies) {      
                    if (RangeCheck(operatorPtr.get(), enemyPtr.get())) {
                        operatorPtr->ChangeOperatorState(OperatorState::ATTACK);
                        int damage = DamageCount(operatorPtr.get(), enemyPtr.get());
                        DamagePerform(damage, enemyPtr.get(), checkpointManager);
                        operatorPtr->attackCD = 0.0f;
                        isAttack = true;
                        break;
                    }
                }
                if (!isAttack) {
					operatorPtr->ChangeOperatorState(OperatorState::IDLE);
				}
            }
        }
    }

    bool ObjectInteraction::RangeCheck(const Operator* op, const Enemy* enemy) {

        auto& enemyPos = enemy->trajectory[enemy->positionIndex];
        int enemyX = enemyPos[0];
        int enemyY = enemyPos[1];

        for (const auto& range : op->attackRange) {
            if (range.x == enemyX && range.y == enemyY) {
                return true;
            }
        }

        return false;
	}

    int ObjectInteraction::DamageCount(const Operator* op, const Enemy* enemy) {
        return op->atk - enemy->def;
    }

    void ObjectInteraction::DamagePerform(int damage,Enemy* enemy,CheckpointManager& checkpointManager) {
        if (enemy->hp > 0) {
            enemy->hp -= damage;
        }
        else {
            enemy->Dead(checkpointManager);
        }
        //DBOUT("The enemy index" << enemy->ID << "'s HP is :" << enemy->hp << endl);
    }
}