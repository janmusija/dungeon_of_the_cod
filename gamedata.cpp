//
// gamedata.cpp
// 2026-10-18
// dungeon_of_the_cod
//

#include "gamedata_def.h"

void GAMEDAT::render_chunk_segment(Chunk* ch, int x, int y, int chx, int chy, int chz, int wid, int ht){
    for (int i = chx; i<chx+wid; i++){
        for (int j = chy; j < chy+ht; j++){
            if (i < CHUNK_WIDTH && j < CHUNK_WIDTH && chz < CHUNK_DEPTH && i >= 0 && j >= 0 && chz >= 0){
                ch->tiles[i][j][chz].render(this, x+i, y+j);
            }
        }
    }
}

void GAMEDAT::render_game(){
    clear();
    render_chunk_segment(camera_chunk,5,5,0,0,0,CHUNK_WIDTH,CHUNK_WIDTH);
    refresh();
    render_ctr++;
}

GAMEDAT::GAMEDAT(uint32_t s){
    seed = s;
    savename = "";
    time = 0;
    render_ctr = 0;
}

void GAMEDAT::tick(){
    // tick all loaded chunks
}

void GAMEDAT::load_chunk(std::string ch){
    // determine if it exists
    std::string s = "save/" + savename + "/" + ch;

    // TK
    // for now just create a new one
    std::string c2 = ch;
    LOADED_CHUNKS.insert(std::make_pair<std::string,Chunk>(std::move(c2),Chunk()));
}

void GAMEDAT::unload_chunk(std::string ch){
    
}