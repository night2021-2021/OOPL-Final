#include "StdAfx.h"
#include "Exusiai.h"

namespace game_framework {

    void Exusiai::SetAttackRange() {
        attackRange.clear();

        for (int i = 0; i <= 3; i++) {
			for (int j = -1; j <= 1; j++) {
				attackRange.push_back({ i, j });
			}
		}

        originalAttackRange = attackRange;
    }

    void Exusiai::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 95);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 95);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 23);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 23);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 23);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 23);
    }

    void Exusiai::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Exusiai/%s/Exusiai_%s_%s/Exusiai_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
    void Exusiai::Skill() {}
};