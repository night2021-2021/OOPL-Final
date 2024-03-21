#pragma once

#include "../Actors/Character/mygame_operator.h"
#include "../Map/mygame_mapAndCheckpoint.h"
#include <string>

namespace game_framework
{
    class OperatorPlacement {
    public:
        OperatorPlacement() = default;

        bool CanPlaceOperator(const Operator& op, const Checkpoint& checkpoint) const;
    };
}