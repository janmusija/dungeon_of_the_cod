//
// gamedata.cpp
// 2026-10-18
// dungeon_of_the_cod
//

#include "gamedata_def.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "creature/creature_maker.h"

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
    render_chunk_segment(camera_chunk,5,5,0,0,camera_z,CHUNK_WIDTH,CHUNK_WIDTH);
    refresh();
    render_ctr++;
}

GAMEDAT::GAMEDAT(uint32_t s){
    seed = s;
    savename = "";
    time = 0;
    render_ctr = 0;
    camera_z = 0;
    rng = std::mt19937(seed);
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
    std::string s = "save/" + savename + "/chunks/" + ch;
    std::filesystem::path p = s;
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
            if (std::getline(is,str,'\n')){
                // get biome
                newchunk.biome = str;
                if (std::getline(is,str,'\n')){
                    // get whether it is populated
                    if (str == "1"){
                        newchunk.populated = true;
                    } else {
                        newchunk.populated = false;
                    }
                    //{auto search = LOADED_CHUNKS.find(ch); std::cout << (search == LOADED_CHUNKS.end());}
                    std::string c2 = ch;
                    LOADED_CHUNKS.insert(std::make_pair<std::string,Chunk>(std::move(c2),std::move(newchunk)));
                    //{auto search = LOADED_CHUNKS.find(ch); std::cout << (search == LOADED_CHUNKS.end());}
                } else {
                    failed_to_load = true;
                }
            } else {
                failed_to_load = true;
            }
        } else {
            failed_to_load = true;
        }
        is.close();
    } else {
        std::string s2 = "save/" + savename + "/chunks/";
        std::filesystem::path p2 = s2;
        if (!std::filesystem::exists(p2)){
            std::filesystem::create_directory(p2);
        }
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
    std::string s = "save/" + savename + "/chunks/" + ch;
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
        if (search->second.populated == true){
            str.push_back('1'); str.push_back('\n');
        } else {
            str.push_back('0'); str.push_back('\n');
        };
        os.open(s);
        os << str;
        os.close();
    } else {
        std::cout << "PROBLEMS"; throw;
    }
}

void GAMEDAT::unload_chunk(std::string ch){
    auto search = LOADED_CHUNKS.find(ch);
    if (search != LOADED_CHUNKS.end()){
        save_chunk(ch);
        LOADED_CHUNKS.erase(search);
    }
}

void GAMEDAT::populate_chunk(std::string ch){
    // add structures etc
}

void GAMEDAT::create_gdata_file(){
    std::string s = "save/" + savename + "/gdat";
    std::ofstream os;
    os.open(s);
    
    os << savename << std::endl;
    os << seed << std::endl;
    os << time << std::endl;
    
    // savename
    // seed
    // time
}

void GAMEDAT::load_gdata_file(std::string filename){
    std::string s = "save/" + filename + "/gdat";

    std::ifstream is;
    std::string str;
    is.open(s);
    if (std::getline(is,str,'\n')){
        savename = str;
        if (std::getline(is,str,'\n')){
            seed = std::stoull(str);
            if (std::getline(is,str,'\n')){
                time = std::stoull(str);
            }
        }
    } else {
        // bad
    }
}

void GAMEDAT::spawn_creature_at(std::string typ, short X, short Y, short Z, std::string CH_ID, bool initdef){
    auto search = LOADED_CHUNKS.find(CH_ID);
    if (search != LOADED_CHUNKS.end() && X >= 0 && X < CHUNK_WIDTH && Y >= 0 && Y < CHUNK_WIDTH && Z >= 0 && Z < CHUNK_DEPTH){
        std::unique_ptr<Creature> c_ptr;

        c_ptr = creature_maker(typ,100,X,Y,Z,CH_ID);// std::make_unique<Creature>(100,X,Y,Z,CH_ID);
        if (initdef){
            c_ptr->initialize_default_stats();
        }
        Tile* tile_ptr = &(search->second.tiles[X][Y][Z]);
        tile_ptr->creatures.push_back(std::move(c_ptr));
    }
}