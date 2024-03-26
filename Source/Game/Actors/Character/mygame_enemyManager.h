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

namespace game_framework {
    class EnemyManager {
    private:
        std::vector<std::unique_ptr<Enemy>> enemies;

        EnemyType stringToEnemyType(const std::string& typeStr) {
            if (typeStr == "BUG_NORMAL") return EnemyType::BUG_NORMAL;
            throw std::runtime_error("Unknown enemy type: " + typeStr);
        }

    public:
        void loadEnemyFromJson(const std::string& enemyJsonFilePath) {
            std::ifstream file(enemyJsonFilePath);
            if (!file.is_open()) {
                std::cerr << "Unable to open file: " << enemyJsonFilePath << std::endl;
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

                auto enemy = std::make_unique<Enemy>(id, maxHp, atk, def, sp, blockCounts, as, ms, trajectory, enemyType);
                enemies.push_back(std::move(enemy));
            }
        }
    };
}
