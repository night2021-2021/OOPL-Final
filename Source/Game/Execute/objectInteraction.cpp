#include "objectInteraction.h"
#include "../mygame.h"
#include <memory>


namespace gaem_framework
{
    void PerformAttacks(std::vector<std::unique_ptr<Operator>>& operators, const std::vector<std::shared_ptr<Enemy>>& enemies) {
        for (auto& op : operators) {
            for (auto& en : enemies) {
                if (IsWithinRange(op.get(), en.get())) {
                    int damage = CalculateDamage(op.get(), en.get());
                    en->reduceHP(damage);                           // Assuming Enemy has a method reduceHP
                    if (en->isDead()) {                             // Assuming Enemy has a method isDead to check health
                        en->handleDeath();                          // Handle enemy death inside Enemy class
                    }
                }
            }
        }
    }

}