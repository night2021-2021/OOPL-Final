#pragma once

#include <afxwin.h> 
#include "mygame_character.h"
#include "../../../Library/gameutil.h"

namespace game_framework {

	class Enemy : public Character 
	{
	public:
		CMovingBitmap image;
		CPoint position;
		float MoveSpeed;


		Enemy(int maxHp, int atk, int def, float attackSpeed, float MoveSpeed)
			:Character(maxHp, atk, def, attackSpeed), MoveSpeed(MoveSpeed)
		{
			HP = maxHp;
		}
	};
}