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
#include "gamedata.h"

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
    
    void render(GAMEDAT* gd, int x, int y);
    Tile(bool wall, bool floor, bool stu, bool std);
    Tile() = default;
};

class Chunk{ // 16 x 16 x 4 grids of tiles
    public:
    Tile tiles[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_DEPTH];
    std::string id;
    uint32_t posx;
    uint32_t posy;
    int32_t posz;
    std::string biome;

    Chunk(); // dummy test
};

#endif