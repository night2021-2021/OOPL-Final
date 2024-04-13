#include "StdAfx.h"
#include "Skadi.h"

namespace game_framework {

    void Skadi::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Skadi::LoadImages() {

        LoadIdleImagesForDirection("front", rightIdleImage, 47);
        LoadIdleImagesForDirection("left", leftIdleImage, 47);
        LoadIdleImagesForDirection("back", backIdleImage, 26);

    }

    void Skadi::LoadIdleImagesForDirection(const char* subfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Skadi/%s/Skadi_%s_Idle/Skadi_%s_Idle_%d.bmp", subfolder, subfolder, subfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Skadi::Skill() {
        if (SP = maxSP) {
            SP = 0;
            ATK += static_cast<int>(ATK * 0.5);
        }
    }
};