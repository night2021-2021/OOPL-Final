#ifndef LOGIC_MAP_H
#define LOGIC_MAP_H

#include <string>
#include <vector>
#include "../nlohmann/json.hpp"

namespace MyNamespace
{
    class Checkpoint {
    public:
        bool walkable;              
        bool placeable;             
        bool occupied;              
        std::string CKPTType;       
        std::string CKPTName;       

        Checkpoint(bool w, bool p, bool o, std::string t, std::string n) 
            : walkable(w), placeable(p), occupied(o), CKPTType(t), CKPTName(n) {}
    };

    class GameMap {
    public:
        int width, height;
        std::vector<std::vector<Checkpoint>> checkpoint;        
        GameMap(int w, int h) : width(w), height(h), checkpoint(h, std::vector<Checkpoint>(w)) {}
    };
}

#endif 