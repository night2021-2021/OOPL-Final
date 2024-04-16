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

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 47);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 47);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 26);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 35);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 35);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 35);

    }

    void Skadi::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Skadi/%s/Skadi_%s_%s/Skadi_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Skadi::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};