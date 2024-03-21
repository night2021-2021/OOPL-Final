#pragma once

#include "mygame_operator.h"
#include "mygame_mapAndCheckpoint.h"
#include <string>

namespace game_framework
{
    class OperatorPlacementManager {
    public:
        OperatorPlacementManager() = default;

        bool CanPlaceOperator(const Operator& op, const Checkpoint& checkpoint) const;
    };
}