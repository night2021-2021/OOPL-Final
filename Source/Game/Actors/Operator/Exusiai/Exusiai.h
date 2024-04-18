#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Exusiai : public Operator
    {
    public:
        Exusiai()
        : Operator(1060, 375, 126, 1, 11, 0, 4, 1.0f, OperatorClass::Sniper, "Exusiai") {

            headImage.LoadBitmapByString({ "resources/characters/operators/Exusiai/Exusiai_Head.bmp" }, RGB(0, 0 ,0));
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

