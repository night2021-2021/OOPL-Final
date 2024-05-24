#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Saria : public Operator
    {
    public:
        Saria()
            : Operator(1833, 320, 442, 3, 15, 15, 40, 1.2f, OperatorClass::Defender, "Saria") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Saria/Saria_Head.bmp" }, RGB(0, 0, 0));
            position.SetPoint(1080, 720);

            LoadImages();
            SetAttackRange();
            image = frontIdleImage;
        }

        void LoadImages() override;
        void LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) override;
        void SetAttackRange() override;
        void Skill() override;
    };
}

