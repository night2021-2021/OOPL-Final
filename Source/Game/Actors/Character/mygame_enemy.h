#ifndef ENEMY_H
#define ENEMY_H

#include <afxwin.h> 
#include "mygame_character.h"
#include "../Game/Map/mygame_checkpointManager.h"
#include "../../../Library/gameutil.h"
#include <vector>
#include <functional>

namespace game_framework {

	enum EnemyState { IDLE, MOVE, ATTACK, DEAD, BLUE_DOOR };

	enum EnemyType { BUG_NORMAL, GIANT_NORMAL };

	enum class EnemyOrientation { Left, Right };

	class Enemy : public Character 
	{
	public:

		CMovingBitmap image;
		CMovingBitmap leftMoveImage;
		CMovingBitmap leftAttackImage;
		CMovingBitmap rightMoveImage;
		CMovingBitmap rightAttackImage;
		CPoint position;				//The real position(pixel)
		int ID;
		int sp;
		int blockCount;	
		int logicX, logicY;					//The logic position in the map
		float moveSpeed;
		float attackCD;
		std::vector<std::vector<int>> trajectory; 		// Moving path
		EnemyType enemyType;  
		EnemyState enemyState; 
		EnemyOrientation enemyOrientation;
		bool isDead = false;
		bool isActive = false;
		bool isBlocked = false;
		int entryTime;					//The time when the enemy enters the map

		size_t  positionIndex;				//The index of the current position in the trajectory

		Enemy(int IDENTIFY, int MAX_HP, int ATK, int DEF, int SP, int BLOCKS, float AS, float MS, const std::vector<std::vector<int>> TRAJECTORY, EnemyType TYPE, int TIME, EnemyOrientation ori = EnemyOrientation::Left)
			:ID(IDENTIFY), Character(MAX_HP, ATK, DEF, AS), sp(SP), blockCount(BLOCKS), moveSpeed(MS), trajectory(TRAJECTORY), enemyType(TYPE), enemyState(IDLE), entryTime(TIME), attackCD(0), enemyOrientation(ori)
		{
			hp = MAX_HP;
			positionIndex = 0;
		};

		void EnterGame();
		void Move(std::vector<int> originalPosition, std::vector<int> nextPosition, CheckpointManager& checkpointManager);
		void Dead(CheckpointManager& checkpointManager);
		void ChangeEnemyState(EnemyState newState);
		void ChangeEnemyOrientation();
		void ChangeImages();

		//Enemy's Load Images
		virtual void LoadImages() {};
		virtual void LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {};
		
		//While enemy reach blue door
		void onReachBlueDoor(CheckpointManager& checkpointManager);
	};
}

#endif