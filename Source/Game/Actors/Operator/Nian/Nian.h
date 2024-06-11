#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Nian : public Operator
    {
    public:
        Nian()
        : Operator(2035, 295, 490, 3, 18, 0, 40, 1.2f, OperatorClass::Defender, "Nian") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Nian/Nian_Head.bmp" }, RGB(0, 0, 0));
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

