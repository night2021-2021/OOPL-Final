#pragma once
#include "mygame_mapAndCheckpoint.h"

namespace game_framework {
    class CheckpointManager {
    public:
        CheckpointManager(GameMap& gameMap) : gameMap(gameMap) {}

        void registerEnemyAtCheckpoint(int x, int y, int enemyBlockCount) {
            Checkpoint& checkpoint = this->gameMap.checkpoint[y][x];
            checkpoint.enemyCount += enemyBlockCount;
        }

        void unregisterEnemyAtCheckpoint(int x, int y, int enemyBlockCount) {
            Checkpoint& checkpoint = this->gameMap.checkpoint[y][x];
            if(checkpoint.enemyCount > 0)checkpoint.enemyCount -= enemyBlockCount;
        }

        void registerOperatorAtCheckpoint(int x, int y, int operatorBlockCount) {
            Checkpoint& checkpoint = this->gameMap.checkpoint[y][x];
            checkpoint.blockCount += operatorBlockCount;
        }

        void unregisterOperatorAtCheckpoint(int x, int y, int operatorBlockCount) {
            Checkpoint& checkpoint = this->gameMap.checkpoint[y][x];
            checkpoint.blockCount -= operatorBlockCount;
        }

        Checkpoint& getCheckpoint(int x, int y) {
            size_t ux = static_cast<size_t>(x);
            size_t uy = static_cast<size_t>(y);

            if (uy >= 0 && uy < this->gameMap.checkpoint.size() &&
                ux >= 0 && ux < this->gameMap.checkpoint[uy].size()) {
                return this->gameMap.checkpoint[uy][ux];
            }else {
                throw std::out_of_range("Coordinates are out of the range of the map dimensions.");
            }
        }

    private:
        GameMap& gameMap; 
    };
}
