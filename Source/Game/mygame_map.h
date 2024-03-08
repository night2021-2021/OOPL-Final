#ifndef MAP_DEFINITIONS_H
#define MAP_DEFINITIONS_H

#include <vector>
namespace MyNamespace
{
    class MapTile {
    public:
        bool walkable;      //敵人可否通行
        bool placeable;     //幹員可否放置
        bool occupied;      //是否有幹員
    };

    class GameMap {
    public:
        int width, height;
        std::vector<std::vector<MapTile>> tiles;        // 二維陣列，用來儲存地圖上每個tile的資訊

        GameMap(int w, int h) : width(w), height(h), tiles(h, std::vector<MapTile>(w)) {}
    };

}

#endif 