// GameMapManager.h
#ifndef GAME_MAP_MANAGER_H
#define GAME_MAP_MANAGER_H

#include "mygame_logicMap.h"
#include <../nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace game_framework {

    class GameMapManager {
    public:
        GameMap loadMapFromJson(const std::string& jsonFilePath) {
            std::ifstream file(jsonFilePath);
            if (!file.is_open()) {
                std::cerr << "無法打開檔案: " << jsonFilePath << std::endl;     // 在這裡應該處理錯誤，可能是拋出異常或返回一個空的 GameMap
            }

            nlohmann::json mapJson;
            file >> mapJson;

            int width = mapJson[0].size();
            int height = mapJson.size();
            GameMap gameMap(width, height);

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    const auto& tileJson = mapJson[y][x];
                    gameMap.checkpoint[y][x] = Checkpoint(
                        tileJson["walkable"],
                        tileJson["placeable"],
                        tileJson["type"],
                        tileJson["name"]
                    );
                }
            }

            return gameMap;
        }
    };
}

#endif 