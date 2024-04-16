#ifndef CHARACTER_H
#define CHARACTER_H

#include <afxwin.h>
namespace game_framework
{
    class Character
    {
        public:
            int maxHp;
            int hp;
            int atk;
            int def;
            float attackSpeed;

            Character(int maxHp, int atk, int def, float attackSpeed)
            : maxHp(maxHp), hp(maxHp), atk(atk), def(def), attackSpeed(attackSpeed) {}

            virtual ~Character() {}
    };
}

#endif