#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Ines : public Operator
    {
    public:
        Ines()
        : Operator(1325, 325, 260, 2, 11, 6, 25, 1.05f, OperatorClass::Vanguard, "Ines") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Ines/Ines_Head.bmp" }, RGB(0, 0, 0));
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

