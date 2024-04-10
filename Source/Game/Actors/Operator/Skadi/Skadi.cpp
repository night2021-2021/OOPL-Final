#include "StdAfx.h"
#include "Skadi.h"

namespace game_framework {

    void Skadi::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });
    }

    void Skadi::Skill() {}
};