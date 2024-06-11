#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Eyjafjalla : public Operator
    {
    public:
        Eyjafjalla()
        : Operator(1100, 470, 90, 1, 18, 0, 4, 1.6f, OperatorClass::Caster, "Eyjafjalla") {

            headImage.LoadBitmapByString({ "resources/characters/operators/Eyjafjalla/Eyjafjalla_Head.bmp" }, RGB(0, 0, 0));
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

