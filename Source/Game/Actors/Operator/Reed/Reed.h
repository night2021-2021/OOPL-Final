#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:
        Reed()
            : Operator(1135, 362, 109, 1, 2.85f, OperatorClass::Medic) {}
    };
}

