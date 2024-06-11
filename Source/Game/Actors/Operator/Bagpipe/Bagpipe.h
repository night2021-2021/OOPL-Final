#pragma once

#include "../../Character/mygame_operator.h"

namespace game_framework
{
    class Bagpipe : public Operator
    {
    public:
        Bagpipe()
        : Operator(1226, 445, 279, 1, 10, 0, 45, 1.0f, OperatorClass::Vanguard, "Bagpipe") {
            headImage.LoadBitmapByString({ "resources/characters/operators/Bagpipe/Bagpipe_Head.bmp" }, RGB(0, 0, 0));
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

