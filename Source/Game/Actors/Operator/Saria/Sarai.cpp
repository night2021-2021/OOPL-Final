#include "StdAfx.h"
#include "Saria.h"

namespace game_framework {

    void Saria::SetAttackRange() {
        attackRange.clear();

        attackRange.push_back({ 0, 0 });

        originalAttackRange = attackRange;
    }

    void Saria::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 47);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 47);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 47);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 27);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 27);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 26);

    }

    void Saria::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Saria/%s/Saria_%s_%s/Saria_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Saria::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};