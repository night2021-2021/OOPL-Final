#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Skadi : public Operator
    {
    public:
        Skadi()
        : Operator(2745, 738, 155, 1, 10, 1.5f, OperatorClass::Guard) {

            std::vector<std::string> imagePaths;
            char buffer[128];

            for (int i = 1; i <= 47; ++i) {
                sprintf(buffer, "resources/characters/operators/Skadi/front/Skadi_Idle/Skadi_Idle_%d.bmp", i);
                imagePaths.push_back(std::string(buffer));
            }

            image.LoadBitmapByString(imagePaths, RGB(255, 255, 255));

            image.SetAnimation(10, false);

            headImage.LoadBitmapByString({ "resources/characters/operators/Skadi/Skadi_Head.bmp" }, RGB(0, 0, 0));
            position.SetPoint(1080, 720);
        }
    };
}

