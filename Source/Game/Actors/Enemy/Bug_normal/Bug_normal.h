#pragma once

#include "../Game/Actors/Character/mygame_enemy.h"

namespace game_framework
{
	class Bug_normal : public Enemy
	{
	public:
        Bug_normal(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::vector<int>> TRAJECTORY, EnemyType TYPE, EnemyState STATE, int TIME)
            : Enemy(IDENTIFY, MAX_HP, ATK, DEF, SP, BLOCKS, AS, MS, TRAJECTORY, TYPE, TIME)
		{
			LoadImages();
			image = leftMoveImage;
		}

        
        void LoadImages() override;
        void LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) override;
	};
}