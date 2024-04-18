#include "StdAfx.h"
#include "Bug_normal.h"

namespace game_framework {

	void Bug_normal::LoadImages() {
		LoadIdleImagesForDirection("N/A", "Move", MoveImage, 58);
        LoadIdleImagesForDirection("N/A", "Attack", AttackImage, 18);
	}

    void Bug_normal::LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {
        std::vector<std::string> imagePaths;
        char buffer[128];
        imagePaths.clear();

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/enimies/Bug_normal/Bug_normal_%s/Bug_normal_%s_%d.bmp", statusfolder, statusfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        imageObject.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        imageObject.SetAnimation(10, false);
    }
}