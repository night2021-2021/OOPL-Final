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
            default:
                return "Unknown Type";
            }
        }

        EnemyType stringToEnemyType(const std::string& typeStr) {
            if (typeStr == "BUG_NORMAL") return EnemyType::BUG_NORMAL;
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
                std::vector<std::string> trajectory = item["Trajectory"].get<std::vector<std::string>>();
                EnemyType enemyType = stringToEnemyType(item["type"].get<std::string>());

                if (enemyType == EnemyType::BUG_NORMAL) {
                    auto enemy = std::make_shared<Bug_normal>(id, maxHp, atk, def, sp, blockCounts, as, ms, trajectory, EnemyType::BUG_NORMAL, EnemyState::IDLE);
                    enemies.push_back(enemy);
                    DBOUT("Created BUG_NORMAL enemy with ID: " << id << std::endl);
                }
            }
        }

        const std::vector<std::shared_ptr<Enemy>>& getEnemies() const {
            return this->enemies;
        }
    };
}