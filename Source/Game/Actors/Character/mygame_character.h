#ifndef CHARACTER_H
#define CHARACTER_H

#include <afxwin.h>
namespace game_framework
{
    class Character
    {
        public:
            int maxHP;
            int HP;
            int ATK;
            int DEF;
            float AttackSpeed;

            Character(int maxHp, int atk, int def, float attackSpeed)
            : maxHP(maxHp), HP(maxHp), ATK(atk), DEF(def), AttackSpeed(attackSpeed) {}

            virtual ~Character() {}
    };
}

#endif