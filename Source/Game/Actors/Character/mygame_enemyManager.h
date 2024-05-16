#include "../../nlohmann/json.hpp"
#include "mygame_enemy.h"

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept> // For std::runtime_error

#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                  \
   OutputDebugString( os_.str().c_str() );  \
}	

namespace game_framework {
    class EnemyManager {
    private:
        std::vector<std::shared_ptr<Enemy>> enemies;

        std::string enemyTypeToString(EnemyType type) {
            switch (type) {
            case EnemyType::BUG_NORMAL:
                return "BUG_NORMAL";
            case EnemyType::GIANT_NORMAL:
                return "GIANT_NORMAL";
            default:
                return "Unknown Type";
            }
        }

        EnemyType stringToEnemyType(const std::string& typeStr) {
            if (typeStr == "BUG_NORMAL") return EnemyType::BUG_NORMAL;
            if (typeStr == "GIANT_NORMAL") return EnemyType::GIANT_NORMAL;
            throw std::runtime_error("Unknown enemy type: " + typeStr);
        }   

    public:
        void loadEnemyFromJson(const std::string& enemyJsonFilePath) {
            std::ifstream file(enemyJsonFilePath);
            if (!file.is_open()) {
                DBOUT("Can't open this file in enemyManager." << endl)
                return;
            }

            nlohmann::json json;
            file >> json;

            for (const auto& item : json["enemies"]) {
                int id = item["ID"];
                int maxHp = item["MaxHP"];
                int atk = item["ATK"];
                int def = item["DEF"];
                float as = item["AS"];
                float ms = item["MS"];
                int sp = item["SP"];
                int blockCounts = item["BlockCounts"];
                std::vector<std::vector<int>> trajectory = item["Trajectory"].get<std::vector<std::vector<int>>>();                 // 0 ¬Oªì©l¦ì¸m
                EnemyType enemyType = stringToEnemyType(item["type"].get<std::string>());
                int time = item["time"];

                if (enemyType == EnemyType::BUG_NORMAL) {
                    auto enemy = std::make_shared<Bug_normal>(id, maxHp, atk, def, sp, blockCounts, as, ms, trajectory, EnemyType::BUG_NORMAL, EnemyState::IDLE, time);
                    enemies.push_back(enemy);
                    DBOUT("Created BUG_NORMAL enemy with ID: " << id << std::endl);
                }else if(enemyType == EnemyType::GIANT_NORMAL) {
                    auto enemy = std::make_shared<Giant_normal>(id, maxHp, atk, def, sp, blockCounts, as, ms, trajectory, EnemyType::GIANT_NORMAL, EnemyState::IDLE, time);
                    enemies.push_back(enemy);
                    DBOUT("Created GIANT_NORMAL enemy with ID: " << id << std::endl);
                }
            }
        }

        const std::vector<std::shared_ptr<Enemy>>& getEnemies() const {
            return this->enemies;
        }
    };
}
