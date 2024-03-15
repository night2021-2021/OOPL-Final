#ifndef REED_H
#define REED_H

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:
        Reed()
        : Operator(1135, 362, 109, 2.85f, OperatorClass::Medic) {}
    };
}

#endif