#ifndef SKADI_H
#define SKADI_H

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Skadi : public Operator
    {
    public:
        Skadi()
        : Operator(1135, 362, 109, 2.85f, OperatorClass::Guard) {}
    };
}

#endif