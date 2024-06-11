#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Dusk : public Operator
    {
    public:
        Dusk()
        : Operator(1141, 582, 95, 1, 30, 0, 40, 2.9f, OperatorClass::Caster, "Dusk") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Dusk/Dusk_Head.bmp" }, RGB(0, 0, 0));
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

