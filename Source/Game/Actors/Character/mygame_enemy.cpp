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

        if (this->position.x != nextPixelX) {
            this->position.x += (this->position.x > nextPixelX) ? -1 : 1;           //Turn left or right
        }

        if (this->position.y != nextPixelY) {
            this->position.y += (this->position.y > nextPixelY) ? -1 : 1;           //Turn up or down
        }

        if (this->position.x == nextPixelX && this->position.y == nextPixelY) {
            if (this->positionIndex + 1 == this->trajectory.size() - 1) {
                Dead();  
            } else {
                this->positionIndex += 1;  
            }
        }
	}

    void Enemy::Dead() {
		this->image.UnshowBitmap();
        this->enemyState = EnemyState::DEAD;
		this->isDead = true;
	}
}