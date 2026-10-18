//
// creature/creature.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef creature_h
#define creature_h

#include "render/render.h"

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

    Fancy_Char symb;


    // skills

    // resistances
};

class Player{ 
    public:
    // pointers to player creatures
    Creature* Target;
};

#endif