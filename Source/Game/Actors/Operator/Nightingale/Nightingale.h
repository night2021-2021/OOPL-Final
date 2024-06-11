#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Nightingale : public Operator
    {
    public:
        Nightingale()
        : Operator(1220, 345, 110, 1, 17, 10, 30, 2.85f, OperatorClass::Medic, "Nightingale") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Nightingale/Nightingale_Head.bmp" }, RGB(0, 0, 0));
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

