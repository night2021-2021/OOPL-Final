#ifndef ENEMY_H
#define ENEMY_H

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
		CPoint position;	//�u�����y�� (pixel)
		int ID;
		int sp;
		int blockCount;	
		float moveSpeed;
		std::vector<std::vector<int>> trajectory; // ���ʸ��u
		EnemyType enemyType;  
		EnemyState enemyState; 
		bool isDead = false;


		int positionIndex;	//�{�b�������(trajectory��index)



		Enemy(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::vector<int>> TRAJECTORY, EnemyType TYPE)
			:ID(IDENTIFY), Character(MAX_HP, ATK, DEF, AS), sp(SP), blockCount(BLOCKS), moveSpeed(MS), trajectory(TRAJECTORY), enemyType(TYPE), enemyState(IDLE)
		{
			HP = MAX_HP;
			positionIndex = 1;
		};
	};
}

#endif