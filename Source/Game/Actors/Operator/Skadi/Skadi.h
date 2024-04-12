#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Skadi : public Operator
    {
    public:
        Skadi()
        : Operator(2745, 738, 155, 1, 10, 1.5f, OperatorClass::Guard) {
            headImage.LoadBitmapByString({ "resources/characters/operators/Skadi/Skadi_Head.bmp" }, RGB(0, 0, 0));
            position.SetPoint(1080, 720);
            
            LoadImagesForOrientation();
            SetAttackRange();
        }

        void SetAttackRange() override;
        void LoadImagesForOrientation() override;
        void Skill();
    };
}

