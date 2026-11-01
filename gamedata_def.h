//
// gamedata_def.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef gamedata_def_h
#define gamedata_def_h
#include "gamedata.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include "map/tile.h"
#include "render/render.h"
#include <random>

class GAMEDAT{
    public:
    uint32_t seed;
    std::string savename;
    std::unordered_map<std::string,Chunk> LOADED_CHUNKS;
    std::mt19937 rng;

    Player player;

    uint64_t time;

    uint8_t render_ctr; // for technical reasons, counter to determine what things to display in a stack

    Chunk* camera_chunk;
    int camera_z;

    GAMEDAT(uint32_t s);
    void render_game();
    void render_chunk_segment(Chunk* ch, int x, int y, int chx, int chy, int chz, int wid, int ht); // the chunk, the position in the screen, the position in the chunk to start with, the width and height of render box
    void tick();

    void load_chunk(std::string ch);

    void unload_chunk(std::string ch);

    void save_chunk(std::string ch);

    void populate_chunk(std::string ch);

    void initialize_save_folders();

    void create_gdata_file();

    void load_gdata_file(std::string filename);

    void spawn_creature_at(std::string typ, short X, short Y, short Z, std::string CH_ID, bool initdef);
};

#endif