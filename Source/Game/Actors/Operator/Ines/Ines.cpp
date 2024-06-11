#include "StdAfx.h"
#include "Ines.h"

namespace game_framework {

    void Ines::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Ines::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 95);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 95);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 95);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 22);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 22);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 23);

    }

    void Ines::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Ines/%s/Ines_%s_%s/Ines_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Ines::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};