#ifndef LOGIC_MAP_H
#define LOGIC_MAP_H

#include <string>
#include <vector>
#include "../nlohmann/json.hpp"

namespace MyNamespace
{
    class MapTile {
    public:
        bool walkable;              
        bool placeable;             
        bool occupied;              
        std::string tileType;       
        std::string tileName;       

        MapTile(bool w, bool p, bool o, std::string t, std::string n) 
            : walkable(w), placeable(p), occupied(o), tileType(t), tileName(n) {}
    };

    class GameMap {
    public:
        int width, height;
        std::vector<std::vector<MapTile>> tiles;        // 二維陣列，用來儲存地圖上每個tile的資訊

        GameMap(int w, int h) : width(w), height(h), tiles(h, std::vector<MapTile>(w)) {}
    };

}

#endif 