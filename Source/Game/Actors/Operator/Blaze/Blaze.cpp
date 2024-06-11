#include "StdAfx.h"
#include "Blaze.h"

namespace game_framework {

    void Blaze::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Blaze::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 46);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 46);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 23);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 23);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 23);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 22);

    }

    void Blaze::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Blaze/%s/Blaze_%s_%s/Blaze_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Blaze::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};