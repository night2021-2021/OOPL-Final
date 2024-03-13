#ifndef MAP_DEFINITIONS_H
#define MAP_DEFINITIONS_H

#include <vector>
namespace MyNamespace
{
    class MapTile {
    public:
        bool walkable;      //�ĤH�i�_�q��
        bool placeable;     //�F���i�_��m
        bool occupied;      //�O�_���F��
    };

    class GameMap {
    public:
        int width, height;
        std::vector<std::vector<MapTile>> tiles;        // �G���}�C�A�Ψ��x�s�a�ϤW�C��tile����T

        GameMap(int w, int h) : width(w), height(h), tiles(h, std::vector<MapTile>(w)) {}
    };

}

#endif 