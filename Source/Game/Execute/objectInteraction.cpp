#include "objectInteraction.h"
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include <memory>


namespace game_framework
{
    void ObjectInteraction::AttackPerform(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies) {

        for (auto& operatorPtr : operators) {
            for (auto& enemyPtr : enemies) {
                if (RangeCheck(operatorPtr.get(), enemyPtr.get())) {

                    int damage = DamageCount(operatorPtr.get(), enemyPtr.get());

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
        return op->ATK - enemy->DEF;
    }
}