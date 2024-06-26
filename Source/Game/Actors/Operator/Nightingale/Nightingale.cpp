#include "StdAfx.h"
#include "Nightingale.h"

namespace game_framework {

    void Nightingale::SetAttackRange(){
        attackRange.clear();

        for (int i = 0; i <= 3; i++) {
            for (int j = -1; j <= 1; j++) {
                attackRange.push_back({ i, j });
            }
        }
        originalAttackRange = attackRange;
    }

    void Nightingale::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 95);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 95);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 23);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 71);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 71);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 71);

    }

    void Nightingale::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Nightingale/%s/Nightingale_%s_%s/Nightingale_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Nightingale::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};