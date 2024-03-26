#pragma once

#include <afxwin.h> 
#include "mygame_character.h"
#include "../../../Library/gameutil.h"
#include <vector>

namespace game_framework {

	enum EnemyState { IDLE, MOVE, ATTACK, DEAD };

	enum EnemyType { BUG_NORMAL };

	class Enemy : public Character 
	{
	public:
		CMovingBitmap image;	
		CPoint position;
		int ID;
		int sp;
		int blockCount;	
		float moveSpeed;
		std::vector<std::string> trajectory;
		EnemyType enemyType;  
		EnemyState enemyState; 



		Enemy(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::string>& TRAJECTORY, EnemyType TYPE)
			:ID(IDENTIFY), Character(MAX_HP, ATK, DEF, AS), sp(SP), blockCount(BLOCKS), moveSpeed(MS), trajectory(TRAJECTORY), enemyType(TYPE), enemyState(IDLE)
		{
			HP = MAX_HP;
		}
	};
}