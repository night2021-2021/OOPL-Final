#ifndef REED_H
#define REED_H

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:
        Reed()
        : Operator(1000, 100, 100, 1.5f, OperatorClass::Medic) {}
    };
}

#endif