#include "StdAfx.h"
#include "Dusk.h"

namespace game_framework {

    void Dusk::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Dusk::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 191);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 191);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 191);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 68);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 68);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 68);

    }

    void Dusk::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Dusk/%s/Dusk_%s_%s/Dusk_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Dusk::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};