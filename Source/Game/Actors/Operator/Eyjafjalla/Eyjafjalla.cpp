#include "StdAfx.h"
#include "Eyjafjalla.h"

namespace game_framework {

    void Eyjafjalla::SetAttackRange() {
        attackRange.clear();

        for (int i = 0; i <= 3; i++) {
			for (int j = -1; j <= 1; j++) {
                if (i == 3 && (j == -1 || j == 1)) {
                    continue;
                }
				attackRange.push_back({ i, j });
			}
		}

        originalAttackRange = attackRange;
    }

    void Eyjafjalla::LoadImages() {

        LoadIdleImagesForDirection("front", "Idle", frontIdleImage, 71);
        LoadIdleImagesForDirection("left", "Idle", leftIdleImage, 71);
        LoadIdleImagesForDirection("back", "Idle", backIdleImage, 22);

        LoadIdleImagesForDirection("front", "Attack", frontAttackImage, 28);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 28);
        LoadIdleImagesForDirection("back", "Attack", backAttackImage, 28);

    }

    void Eyjafjalla::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Eyjafjalla/%s/Eyjafjalla_%s_%s/Eyjafjalla_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }

    void Eyjafjalla::Skill() {}
};