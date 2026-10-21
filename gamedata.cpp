//
// gamedata.cpp
// 2026-10-18
// dungeon_of_the_cod
//

#include "gamedata_def.h"
#include <filesystem>
#include <fstream>
#include <iostream>

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

void GAMEDAT::initialize_save_folders(){
    std::filesystem::path savedir = "save";
    if (!std::filesystem::exists(savedir)) {
        std::filesystem::create_directory(savedir);
    }
    savedir = savedir / savename;
    if (!std::filesystem::exists(savedir)) {
        std::filesystem::create_directory(savedir);
    }
}

/*
Chunk file format

first 16*16*4 chars: structure of the level


*/

void GAMEDAT::load_chunk(std::string ch){
    // determine if it exists
    std::string s = "save/" + savename + "/" + ch;
    std::filesystem::path p = s;
    //std::cout << s << std::endl;
    bool failed_to_load = false;
    if (std::filesystem::exists(p)){
        std::ifstream is;
        std::string str; 
        is.open(s);
        std::string c2;
        Chunk newchunk;
        if (std::getline(is,str,'\n') && str.length() >= CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_DEPTH){
            for (int i = 0; i< CHUNK_WIDTH*CHUNK_WIDTH*CHUNK_DEPTH; i++){
                Tile* tile_ptr = &(newchunk.tiles[i%CHUNK_WIDTH][(i/CHUNK_WIDTH)%CHUNK_WIDTH][(i/(CHUNK_WIDTH*CHUNK_WIDTH))]);
                //std::cout << str[i];
                if (str[i] == '_') {
                    tile_ptr->haswall = false;
                    tile_ptr->hasfloor = false;
                    tile_ptr->stairup = false;
                    tile_ptr->stairdown = false;
                } else if (str[i] == '.'){
                    tile_ptr->haswall = false;
                    tile_ptr->hasfloor = true;
                    tile_ptr->stairup = false;
                    tile_ptr->stairdown = false;
                } else if (str[i] == '#'){
                    tile_ptr->haswall = true;
                    tile_ptr->hasfloor = true;
                    tile_ptr->stairup = false;
                    tile_ptr->stairdown = false;
                } else if (str[i] == '<'){
                    tile_ptr->haswall = false;
                    tile_ptr->hasfloor = true;
                    tile_ptr->stairup = true;
                    tile_ptr->stairdown = false;
                } else if (str[i] == '>'){
                    tile_ptr->haswall = false;
                    tile_ptr->hasfloor = true;
                    tile_ptr->stairup = false;
                    tile_ptr->stairdown = true;
                } else if (str[i] == 'X'){
                    tile_ptr->haswall = false;
                    tile_ptr->hasfloor = true;
                    tile_ptr->stairup = true;
                    tile_ptr->stairdown = true;
                } 
            }
            // further loading details

            //{auto search = LOADED_CHUNKS.find(ch); std::cout << (search == LOADED_CHUNKS.end());}
            std::string c2 = ch;
            LOADED_CHUNKS.insert(std::make_pair<std::string,Chunk>(std::move(c2),std::move(newchunk)));
            //{auto search = LOADED_CHUNKS.find(ch); std::cout << (search == LOADED_CHUNKS.end());}
            is.close();
        } else {
            failed_to_load = true;
            is.close();
        }
    } else {
        failed_to_load = true;
    }
    if (failed_to_load){
    //std::cout << "bad\n";
    // TK -- chunk generation
    std::string c2 = ch;
    LOADED_CHUNKS.insert(std::make_pair<std::string,Chunk>(std::move(c2),Chunk()));

    save_chunk(ch);
    }
}

void GAMEDAT::save_chunk(std::string ch){
    std::string s = "save/" + savename + "/" + ch;
    std::ofstream os;
    std::string str;
    auto search = LOADED_CHUNKS.find(ch);
    if (search != LOADED_CHUNKS.end()) {
        for (int k = 0; k < CHUNK_DEPTH; k++){
            for (int j = 0; j < CHUNK_WIDTH; j++){
                for (int i = 0; i< CHUNK_WIDTH; i++){
                    Tile* tile_ptr = &(search->second.tiles[i][j][k]);
                    char garfield = '_';
                    if (tile_ptr->haswall){
                        garfield = '#';
                    } else if (tile_ptr->stairup && tile_ptr->stairdown){
                        garfield = 'X';
                    } else if (tile_ptr->stairup) {
                        garfield = '<';
                    } else if (tile_ptr->stairdown){
                        garfield = '>';
                    } else if (tile_ptr->hasfloor){
                        garfield = '.';
                    }
                    str.push_back(garfield);
                }
            }
        }
        str.push_back('\n');
        str = str + (search->second.biome + "\n");
        os.open(s);
        os << str;
        os.close();
    } else {
        std::cout << "PROBLEMS"; throw;
    }
}

void GAMEDAT::unload_chunk(std::string ch){
    save_chunk(ch);

}