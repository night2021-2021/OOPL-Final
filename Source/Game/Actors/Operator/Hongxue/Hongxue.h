#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Hongxue : public Operator
    {
    public:
        Hongxue()
        : Operator(1060, 375, 126, 1, 11, 0, 4, 1.0f, OperatorClass::Sniper, "Hongxue") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Hongxue/Hongxue_Head.bmp" }, RGB(0, 0, 0));
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

