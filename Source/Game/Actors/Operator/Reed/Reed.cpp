#include "StdAfx.h"
#include "Reed.h"

namespace game_framework {

    void Reed::SetAttackRange() {
        attackRange.clear();

        for (int i = 0; i <= 3; i++) {
			for (int j = -1; j <= 1; j++) {
				attackRange.push_back({ i, j });
			}
		}

        originalAttackRange = attackRange;
    }

    void Reed::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 143);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 143);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 143);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 33);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 33);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 37);

    }

    void Reed::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Reed/%s/Reed_%s_%s/Reed_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
    void Reed::Skill() {}
};