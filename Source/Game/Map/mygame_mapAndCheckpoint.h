#ifndef LOGIC_MAP_H
#define LOGIC_MAP_H

#include <string>
#include <vector>

#include "../Library/gameutil.h"
#include "../nlohmann/json.hpp"

namespace game_framework
{
    class Checkpoint {          //A checkpoint is a single point on the map, which has lots peremeter   
    public:
        bool walkable;              
        bool placeable;             
        bool occupied;              
        int enemyCount;
        int blockCount;         //operator block count
        int visualX, visualY;   //pixel
        int logicX, logicY;     //logic
        std::string CKPTType;       
        std::string CKPTName;   //Height is Englsih, Width is Math   

        CMovingBitmap attackRangePoint;  //Attack range point

        Checkpoint() : walkable(false), placeable(false), occupied(false), enemyCount(0), blockCount(0) ,visualX(0), visualY(0), logicX(0), logicY(0){}       //Default constructor

        Checkpoint(bool w, bool p, std::string t, std::string n, int lx, int ly)
            : walkable(w), placeable(p), occupied(false), enemyCount(0), blockCount(0), visualX(0), visualY(0), logicX(lx), logicY(ly), CKPTType(t), CKPTName(n) {}	   //Constructor
        
    };

    class GameMap {             //A game map is a 2D array of Checkpoints
    public:
        int width, height;
        std::vector<std::vector<Checkpoint>> checkpoint;       

        GameMap() : width(0), height(0) {}

        GameMap(int w, int h) : width(w), height(h), checkpoint(h, std::vector<Checkpoint>(w)) {}       
    };
}

#endif 