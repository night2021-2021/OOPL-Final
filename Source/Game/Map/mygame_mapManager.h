// GameMapManager.h
#ifndef GAME_MAP_MANAGER_H
#define GAME_MAP_MANAGER_H

#include "../nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                  \
   OutputDebugString( os_.str().c_str() );  \
}	

namespace game_framework {

    class GameMapManager {
    private:
		GameMap gameMap;
    public:


        void loadLogicMapFromJson(const std::string& logicJsonFilePath) {
            std::ifstream logicFile(logicJsonFilePath);
            if (!logicFile.is_open()) {
                DBOUT("Failed to open file: " << logicJsonFilePath << "\n");        //Check if the file isn't opened
                throw std::runtime_error("Cannot open file: " + logicJsonFilePath);
            }

            nlohmann::json logicMapJson;
            logicFile >> logicMapJson;

            int width = logicMapJson[0].size();
            int height = logicMapJson.size();
            this ->gameMap = GameMap(width, height);

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    const auto& tileJson = logicMapJson[y][x];
                    gameMap.checkpoint[y][x] = Checkpoint(
                        tileJson["walkable"],
                        tileJson["placeable"], 
                        tileJson["type"],
                        tileJson["name"]
                    );
                    DBOUT("Checkpoint: " << tileJson["name"] << " at (" << x << ", " << y << ")\n"); //check if the checkpoint is loaded
                }
            }
        }

        void loadVisualMapFromJson(const std::string& visualJsonFilePath) {        

			std::ifstream visualFile(visualJsonFilePath);
            if (!visualFile.is_open()) {
                DBOUT("Failed to open file: " << visualJsonFilePath << "\n");        //Check if the file is not opened
                throw std::runtime_error("Cannot open file: " + visualJsonFilePath);
			}

			nlohmann::json visualJson;
            visualFile >> visualJson;

            for (const auto& checkpointJson : visualJson) {
                std::string checkpointName = checkpointJson["Checkpoint"];
                int visualX = checkpointJson["x"];
                int visualY = checkpointJson["y"];
                DBOUT("VisualX is :" << visualX << ", and the visualY is :" << visualY << endl);

                for (auto& row : gameMap.checkpoint) {
                    for (auto& checkpoint : row) {
                        if (checkpoint.CKPTName == checkpointName) {
                            checkpoint.visualX = visualX;
                            checkpoint.visualY = visualY;
                            DBOUT("Updated checkpoint: " << checkpointName << " to (" << visualX << ", " << visualY << ")\n");      //check if the visual checkpoint is updated
                            break; 
                        }
                    }
                }
            }
		}

        GameMap& getGameMap() {
            return this->gameMap;
        }

        // vector<int> getPointFromLogic(int logicX, int logicY)
        // {
        //     std::ifstream visualFile(visualJsonFilePath);
        //     if (!visualFile.is_open()) {
        //         DBOUT("Failed to open file: " << visualJsonFilePath << "\n");        //Check if the file is not opened
        //         throw std::runtime_error("Cannot open file: " + visualJsonFilePath);
		// 	}

		// 	nlohmann::json visualJson;
        //     visualFile >> visualJson;

        //     for (const auto& checkpointJson : visualJson) {
        //         std::string checkpointName = checkpointJson["Checkpoint"];
        //         int visualX = checkpointJson["x"];
        //         int visualY = checkpointJson["y"];
        //         DBOUT("VisualX is :" << visualX << ", and the visualY is :" << visualY << endl);

        //         for (auto& row : gameMap.checkpoint) {
        //             for (auto& checkpoint : row) {
        //                 if (checkpoint.CKPTName == checkpointName) {
        //                     checkpoint.visualX = visualX;
        //                     checkpoint.visualY = visualY;
        //                     DBOUT("Updated checkpoint: " << checkpointName << " to (" << visualX << ", " << visualY << ")\n");      //check if the visual checkpoint is updated
        //                     break; 
        //                 }
        //             }
        //         }
        //     }
        // }
    };
}

#endif 