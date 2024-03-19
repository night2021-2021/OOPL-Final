// GameMapManager.h
#ifndef GAME_MAP_MANAGER_H
#define GAME_MAP_MANAGER_H

#include "mygame_mapAndCheckpoint.h"
#include "../nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace game_framework {

    class GameMapManager {
    private:
		GameMap gameMap;
    public:
        GameMap loadLogicMapFromJson(const std::string& logicJsonFilePath) {
            std::ifstream logicFile(logicJsonFilePath);
            if (!logicFile.is_open()) {
                throw std::runtime_error("Cannot open file: " + logicJsonFilePath);
            }

            nlohmann::json logicMapJson;
            logicFile >> logicMapJson;

            int width = logicMapJson[0].size();
            int height = logicMapJson.size();
            GameMap gameMap(width, height);

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    const auto& tileJson = logicMapJson[y][x];
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

        void loadVisualMapFromJson(const std::string& visualJsonFilePath) {
			std::ifstream visualFile(visualJsonFilePath);
            if (!visualFile.is_open()) {
                throw std::runtime_error("Cannot open file: " + visualJsonFilePath);
			}

			nlohmann::json visualJson;
            visualFile >> visualJson;

            for (const auto& checkpointJson : visualJson) {
                std::string checkpointName = checkpointJson["Checkpoint"];
                int visualX = checkpointJson["x"];
                int visualY = checkpointJson["y"];

                for (auto& row : gameMap.checkpoint) {
                    for (auto& checkpoint : row) {
                        if (checkpoint.CKPTName == checkpointName) {
                            checkpoint.visualX = visualX;
                            checkpoint.visualY = visualY;
                            break; 
                        }
                    }
                }
            }
		}
    };
}

#endif 