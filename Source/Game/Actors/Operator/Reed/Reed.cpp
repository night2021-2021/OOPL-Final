#include "StdAfx.h"
#include "Reed.h"

namespace game_framework {

    void Reed::SetAttackRange() {
        attackRange.clear();

        for (int i = 0; i <= 3; i++) {
			for (int j = -1; j <= 1; j++) {
				attackRange.push_back({ i, j });
			}
		}

        originalAttackRange = attackRange;
    }

    void Reed::Skill() {}
};