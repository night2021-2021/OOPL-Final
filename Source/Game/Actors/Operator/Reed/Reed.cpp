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

        LoadIdleImagesForDirection("front", rightIdleImage, 143);
        LoadIdleImagesForDirection("left", leftIdleImage, 143);
        LoadIdleImagesForDirection("back", backIdleImage, 143);

    }

    void Reed::LoadIdleImagesForDirection(const char* subfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Reed/%s/Reed_%s_Idle/Reed_%s_Idle_%d.bmp", subfolder, subfolder, subfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
    void Reed::Skill() {}
};