#include "stdafx.h"
#include <vector>
#include "../Library/gameutil.h"
#include "mygame_enemy.h"

namespace  game_framework {

    void Enemy::EnterGame() {
        std::vector<int> startPosition = trajectory.front();
        logicX = startPosition[0];
        logicY = startPosition[1];
    }

    void Enemy::Move(std::vector<int> originalPosition, std::vector<int> nextPosition, CheckpointManager& checkpointManager){
		
        int originalPixelX = originalPosition[0];
        int originalPixelY = originalPosition[1];
        int nextPixelX = nextPosition[0];
        int nextPixelY = nextPosition[1];

        if (this->isActive) {
            if (this->position.x != nextPixelX && !this->isBlocked) {
                this->position.x += (this->position.x > nextPixelX) ? -1 : 1;           //Turn left or right
            }

            if (this->position.y != nextPixelY && !this->isBlocked) {
                this->position.y += (this->position.y > nextPixelY) ? -1 : 1;           //Turn up or down
            }

            if (this->position.x == nextPixelX && this->position.y == nextPixelY) {     //If the enemy reaches the next position
                if (this->positionIndex + 1 == this->trajectory.size() - 1) {		    //Go to blue door 
                    Dead(checkpointManager);
                    onReachBlueDoor();

                } else {
                    this->logicX = this->trajectory[this->positionIndex + 1][0];
                    this->logicY = this->trajectory[this->positionIndex + 1][1];
                    this->positionIndex += 1;                                           //Move to the next position
                }
            }
        }
	}

    void Enemy::Dead(CheckpointManager& checkpointManager) {
        this->enemyState = EnemyState::DEAD;
		this->isDead = true;
        checkpointManager.unregisterEnemyAtCheckpoint(this->logicX, this->logicY, this->blockCount);
	}

    void Enemy::ChangeEnemyState(EnemyState newState)
    {
        if (enemyState != newState)
        {
			enemyState = newState;
            ChangeImages();
		}
    }

    void Enemy::ChangeImages() {
        switch (enemyState) {
		case EnemyState::IDLE:
			this->image = this->MoveImage;
			break;
		case EnemyState::MOVE:
			this->image = this->MoveImage;
			break;
		case EnemyState::ATTACK:
			this->image = this->AttackImage;
			break;
		case EnemyState::DEAD:
			break;
		}
	}
}