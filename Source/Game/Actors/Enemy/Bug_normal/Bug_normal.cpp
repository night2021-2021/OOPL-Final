#include "StdAfx.h"
#include "Bug_normal.h"

namespace game_framework {

	void Bug_normal::LoadImages() {
		LoadIdleImagesForDirection("left", "Move", leftMoveImage, 46);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 14);
        LoadIdleImagesForDirection("right", "Move", rightMoveImage, 46);
        LoadIdleImagesForDirection("right", "Attack", rightAttackImage, 14);
	}

    void Bug_normal::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/enimies/Bug_normal/%s/Bug_normal_%s_%s/Bug_normal_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
}