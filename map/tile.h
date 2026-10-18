//
// map/tile.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef tile_h
#define tile_h

#include <vector>
#include "creature/creature.h"
#include "item/item.h"

/*

*/

class Tile{
    public:
    bool haswall; // if true, not passable
    bool hasfloor; // if true, things standing on it do not fall down, and things standing below can climb up to a nearby ledge
    bool stairup; // if true, can go up
    bool stairdown; // if true, can go down
    std::vector<Creature*> creatures;
    std::vector<Item*> items;
};

class Chunk{ // 16 x 16 x 4 grids of tiles
    public:
    Tile[16][16][4] tiles;
    std::string id;
    uint32_t posx;
    uint32_t posy;
    uint32_t posz;
    std::string biome;
};

#endif