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
		CPoint position;	//The real position(pixel)
		int ID;
		int sp;
		int blockCount;	
		float moveSpeed;
		std::vector<std::vector<int>> trajectory; 		// Moveing path
		EnemyType enemyType;  
		EnemyState enemyState; 
		bool isDead = false;
		bool isBlocked = false;


		int positionIndex;				//The index of the current position in the trajectory

		Enemy(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::vector<int>> TRAJECTORY, EnemyType TYPE)
			:ID(IDENTIFY), Character(MAX_HP, ATK, DEF, AS), sp(SP), blockCount(BLOCKS), moveSpeed(MS), trajectory(TRAJECTORY), enemyType(TYPE), enemyState(IDLE)
		{
			hp = MAX_HP;
			positionIndex = 1;
		};

		void Move(std::vector<int> originalPosition, std::vector<int> nextPosition);
		void Dead();
	};
}

#endif