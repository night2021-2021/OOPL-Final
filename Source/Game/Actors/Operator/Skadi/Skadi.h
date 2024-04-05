#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Skadi : public Operator
    {
    public:
        Skadi()
        : Operator(2745, 738, 155, 1, 10, 1.5f, OperatorClass::Guard) {}
    };
}

