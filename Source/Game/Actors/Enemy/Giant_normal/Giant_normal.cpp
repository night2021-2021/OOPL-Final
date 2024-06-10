#include "StdAfx.h"
#include "Giant_normal.h"

namespace game_framework {

	void Giant_normal::LoadImages() {
        LoadIdleImagesForDirection("left", "Move", leftMoveImage, 27);
        LoadIdleImagesForDirection("left", "Attack", leftAttackImage, 12);
        LoadIdleImagesForDirection("right", "Move", rightMoveImage, 27);
        LoadIdleImagesForDirection("right", "Attack", rightAttackImage, 12);
	}

    void Giant_normal::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/enimies/Giant_normal/%s/Giant_normal_%s_%s/Giant_normal_%s_%s_%d.bmp", subfolder, subfolder, statusfolder, subfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
}