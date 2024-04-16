#include "stdafx.h"
#include <vector>
#include "../Library/gameutil.h"
#include "mygame_enemy.h"

namespace  game_framework {
    void Enemy::Move(std::vector<int> originalPosition, std::vector<int> nextPosition){
		
        
        int originalPixelX = originalPosition[0];
        int originalPixelY = originalPosition[1];
        int nextPixelX = nextPosition[0];
        int nextPixelY = nextPosition[1];

        if (this->position.x != nextPixelX){
            if (this->position.x > nextPixelX){ // 要往左走
                this->position.x -= 1;
            }
            else{   //要往右走
                this->position.x += 1;
            }
        }

        if (this->position.y != nextPixelY){
            if (this->position.y > nextPixelY){ // 要往上走
                this->position.y -= 1;
            }
            else{
                this->position.y += 1;
            }
        }

        int index = this->positionIndex;
        int stepSize = this->trajectory.size();

        if (index + 1 == stepSize - 1 && this->position.x == nextPixelX && this->position.y == nextPixelY)
        {
            Dead();
        }
        else if( this->position.x == nextPixelX && this->position.y == nextPixelY)
        {
            this->positionIndex += 1;
        }
	}

    void Enemy::Dead() {
		this->image.UnshowBitmap();
        this->enemyState = EnemyState::DEAD;
		this->isDead = true;
	}
}