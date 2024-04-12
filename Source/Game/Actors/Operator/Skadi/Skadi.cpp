#include "StdAfx.h"
#include "Skadi.h"

namespace game_framework {

    void Skadi::SetAttackRange(){
        attackRange.clear();

        attackRange.push_back({ 0, 0 });
        attackRange.push_back({ 1, 0 });

        originalAttackRange = attackRange;
    }

    void Skadi::LoadImagesForOrientation() {
        std::vector<std::string> imagePaths;
        char buffer[128];

        const char* subfolder = "";
        int imageCount = 0; 
        imagePaths.clear();

        switch (orientation) {
        case Orientation::Up:
            subfolder = "back";
            imageCount = 26; 
            break;
        case Orientation::Down:
			subfolder = "front";
			imageCount = 47; 
			break;
        case Orientation::Left:
            subfolder = "front";
			imageCount = 47; 
			break;  
        case Orientation::Right:
            subfolder = "front";
            imageCount = 47; 
            break;
        }

        for (int i = 1; i <= imageCount; ++i) {
            sprintf(buffer, "resources/characters/operators/Skadi/%s/Skadi_%s_Idle/Skadi_%s_Idle_%d.bmp", subfolder, subfolder, subfolder, i);
            imagePaths.push_back(std::string(buffer));
        }

        image = CMovingBitmap();
        image.LoadBitmapByString(imagePaths, RGB(255, 255, 255));
        image.SetAnimation(10, false); 
    }

    void Skadi::Skill() {}
};