#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Blaze : public Operator
    {
    public:
        Blaze()
        : Operator(1858, 495, 245, 2, 19, 0, 40, 1.2f, OperatorClass::Guard, "Blaze") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Blaze/Blaze_Head.bmp" }, RGB(0, 0, 0));
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

