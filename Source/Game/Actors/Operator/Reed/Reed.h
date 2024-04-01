#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:

        Reed()
        : Operator(1135, 362, 109, 1, 12, 2.85f, OperatorClass::Medic) {

            std::vector<std::string> imagePaths;
            char buffer[128];

            for (int i = 1; i <= 142; ++i) {
                sprintf(buffer, "resources/characters/operators/Reed/front/idle/reed_front_idle_%d.bmp", i);
                imagePaths.push_back(std::string(buffer));
            }

            image.LoadBitmapByString(imagePaths, RGB(255, 255, 255));

            image.SetAnimation(10, false);

            headImage.LoadBitmapByString({ "resources/characters/operators/Reed/Reed_Head.bmp" }, RGB(255, 255, 255));
            position.SetPoint(1080, 720);
        }
    };
}

