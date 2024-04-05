#pragma once

#include "../Game/Actors/Character/mygame_enemy.h"

namespace game_framework
{
	class Bug_normal : public Enemy
	{
	public:
        Bug_normal(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::string>& TRAJECTORY, EnemyType TYPE, EnemyState STATE)
            : Enemy(IDENTIFY, MAX_HP, ATK, DEF, SP, BLOCKS, AS, MS, TRAJECTORY, TYPE)
		{
            image.LoadBitmapByString({
                "resources/characters/enimies/Bug_normal/frame_01.bmp",
                "resources/characters/enimies/Bug_normal/frame_02.bmp",
                "resources/characters/enimies/Bug_normal/frame_03.bmp",
                "resources/characters/enimies/Bug_normal/frame_04.bmp",
                "resources/characters/enimies/Bug_normal/frame_05.bmp",
                "resources/characters/enimies/Bug_normal/frame_06.bmp",
                "resources/characters/enimies/Bug_normal/frame_07.bmp",
                "resources/characters/enimies/Bug_normal/frame_08.bmp",
                "resources/characters/enimies/Bug_normal/frame_09.bmp",
                "resources/characters/enimies/Bug_normal/frame_010.bmp",
                "resources/characters/enimies/Bug_normal/frame_011.bmp",
                "resources/characters/enimies/Bug_normal/frame_012.bmp",
                "resources/characters/enimies/Bug_normal/frame_013.bmp",
                "resources/characters/enimies/Bug_normal/frame_014.bmp",
                "resources/characters/enimies/Bug_normal/frame_015.bmp",
                "resources/characters/enimies/Bug_normal/frame_016.bmp",
                "resources/characters/enimies/Bug_normal/frame_017.bmp",
                "resources/characters/enimies/Bug_normal/frame_018.bmp",
                "resources/characters/enimies/Bug_normal/frame_019.bmp",
                "resources/characters/enimies/Bug_normal/frame_020.bmp",
                "resources/characters/enimies/Bug_normal/frame_021.bmp",
                "resources/characters/enimies/Bug_normal/frame_022.bmp",
                "resources/characters/enimies/Bug_normal/frame_023.bmp",
                "resources/characters/enimies/Bug_normal/frame_024.bmp"
                }, RGB(255, 255, 255));
			image.SetAnimation(10, false);

			position.SetPoint(1000, 100);
		}
	};
}