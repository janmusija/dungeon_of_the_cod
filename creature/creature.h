//
// creature/creature.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef creature_h
#define creature_h

#include "render/render.h"
#include <unordered_map>
#include "gamedata.h"
#include <string>

class Creature{
    public:
    bool AI;
    bool alive;
    uint32_t hp;

    // position in chunk
    short x;
    short y;
    short z;
    std::string chunkid;

    Fancy_Char* symb;

    // type of creature
    std::string name;
    std::string type;

    // skills
    std::unordered_map<std::string,uint32_t> skills;

    // resistances
    std::unordered_map<std::string,float>* resistances;

    // inventory


    // functions
    void damage(std::unordered_map<std::string,uint32_t>& damage_vector);
};

class Player{ 
    public:
    // pointers to player creatures
    Creature* Target;
};

#endif