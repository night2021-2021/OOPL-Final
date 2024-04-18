#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Reed : public Operator
    {
    public:
        Reed()
        : Operator(1135, 362, 109, 1, 12, 10, 35, 1.85f, OperatorClass::Medic, "Reed") {

            headImage.LoadBitmapByString({ "resources/characters/operators/Reed/Reed_Head.bmp" }, RGB(255, 255, 255));
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

