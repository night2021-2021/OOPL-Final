#include "StdAfx.h"
#include "Nian.h"

namespace game_framework {

    void Nian::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });

        originalAttackRange = attackRange;
    }

    void Nian::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 63);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 63);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 63);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 24);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 24);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 35);

    }

    void Nian::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Nian/%s/Nian_%s_%s/Nian_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Nian::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};