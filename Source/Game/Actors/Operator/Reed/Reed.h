#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:
        Reed()
        : Operator(1135, 362, 109, 1, 12, 2.85f, OperatorClass::Medic) {
            image.LoadBitmapByString({ "resources/characters/operators/Reed/Reed.bmp" }, RGB(255, 255, 255));
            headImage.LoadBitmapByString({ "resources/characters/operators/Reed/Reed_Head.bmp" }, RGB(255, 255, 255));
            position.SetPoint(1080, 720);
        }
    };
}

