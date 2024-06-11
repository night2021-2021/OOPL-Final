#include "StdAfx.h"
#include "Bagpipe.h"

namespace game_framework {

    void Bagpipe::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Bagpipe::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 47);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 47);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 47);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 8);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 8);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 20);

    }

    void Bagpipe::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Bagpipe/%s/Bagpipe_%s_%s/Bagpipe_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Bagpipe::Skill() {
        if (sp = maxSp) {
            sp = 0;
            atk += static_cast<int>(atk * 0.5);
        }
    }
};