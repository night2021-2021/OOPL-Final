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
    void ObjectInteraction::OperatorAttackPerform(std::vector<std::unique_ptr<Operator>>& operators, std::vector<std::shared_ptr<Enemy>>& enemies, float deltaTime, CheckpointManager& checkpointManager) {
        for (auto& operatorPtr : operators) {
            if (!operatorPtr->isPlaced)
            {
				continue;
			}

            operatorPtr->attackCD += deltaTime;
            if (operatorPtr->attackCD >= operatorPtr->attackSpeed) {
                bool isAttack = false;                      //Once the operator attacks, the state will be changed to ATTACK    (Operator can cattack and only attack one enemy at same time.)
                for (auto& enemyPtr : enemies) {      
                    if (OperatorRangeCheck(operatorPtr.get(), enemyPtr.get()) && !enemyPtr->isDead) {
                        operatorPtr->ChangeOperatorState(OperatorState::ATTACK);
                        int damage = OperatorDamageCount(operatorPtr.get(), enemyPtr.get());
                        OperatorDamagePerform(damage, enemyPtr.get(), checkpointManager);
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

    bool ObjectInteraction::OperatorRangeCheck(const Operator* op, const Enemy* enemy) {

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

    int ObjectInteraction::OperatorDamageCount(const Operator* op, const Enemy* enemy) {
        return max(op->atk - enemy->def, 1);
    }

    void ObjectInteraction::OperatorDamagePerform(int damage,Enemy* enemy,CheckpointManager& checkpointManager) {
        DBOUT("The enemy index " << enemy->ID << "'s HP is :" << enemy->hp << endl);
        enemy->hp -= damage;
        if (enemy->hp <= 0) {
            enemy->Dead(checkpointManager);
        }
    }

    //The operator attack enemy
    //-----------------------------------------------------------------------------------------------------------
    //The enemy attack operator

    void ObjectInteraction::EnemyAttackPerform(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Operator>>& operators, float deltaTime, CheckpointManager& checkpointManager) {
        for (auto& enemyPtr : enemies) {
            if (enemyPtr->isDead || !enemyPtr->isActive) continue;             //Jump loop while enemy dead or not active                                  

            enemyPtr->attackCD += deltaTime;
            if (enemyPtr->attackCD >= enemyPtr->attackSpeed) {
                for (auto& operatorPtr : operators) {
                    if (EnemyRangeCheck(operatorPtr.get(), enemyPtr.get())) {                  
                        enemyPtr->ChangeEnemyState(EnemyState::ATTACK);                 
                        int damage = EnemyDamageCount(operatorPtr.get(), enemyPtr.get());      
                        EnemyDamagePerform(damage, operatorPtr.get(), checkpointManager);
                        enemyPtr->attackCD = 0.0f;                                      
                        break;                                                          
                    }
                }
            }
        }
    }

    bool ObjectInteraction::EnemyRangeCheck(const Operator* op, const Enemy* enemy) {
        if (op->logicX == enemy->logicX && op->logicY == enemy->logicY && op->isPlaced)
            return true;
        return false;
    }

    int ObjectInteraction::EnemyDamageCount(const Operator* op, const Enemy* enemy) {
        return max(enemy->atk - op->def, 1);
    }

    void ObjectInteraction::EnemyDamagePerform(int damage, Operator* op, CheckpointManager& checkpointManager) {
        if (op->isAlive) {
            if (op->hp > 0) {
			    op->hp -= damage;
		    }
            else {
			    op->Retreat(checkpointManager);
		    }
            DBOUT("Operator "<< op->operatorName <<" HP is :" << op->hp << endl);
        }
	}
}