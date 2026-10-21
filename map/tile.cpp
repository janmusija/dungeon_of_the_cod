//
// map/tile.cpp
// 2026-10-18
// dungeon_of_the_cod
//

#include "map/tile.h"
#include "render/render.h"
#include "gamedata_def.h"
#include <iostream>

void Tile::render(GAMEDAT* gd, int x, int y){
    if (haswall) {
        render_char_bg(x,y,Fancy_Char(L' ',0),7);
    } else {
        if (creatures.size() > 0){
            uint8_t bgcolor = 0;
            int index = gd->render_ctr%items.size();
            if (!hasfloor && !stairdown && !stairup){bgcolor = 3;}
            render_char_bg(x,y,creatures[index]->symb,bgcolor);
        } else if (items.size() > 0) {
            uint8_t bgcolor = 0;
            int index = gd->render_ctr%items.size();
            if (!hasfloor && !stairdown && !stairup){bgcolor = 3;}
            render_char_bg(x,y,items[index]->symb,bgcolor);
        } else {
            if (stairdown && stairup){
                render_char(x,y,Fancy_Char(L'X',15));
            } else if (stairdown){
                render_char(x,y,Fancy_Char(L'>',15));
            } else if (stairup){
                render_char(x,y,Fancy_Char(L'<',15));
            } else if (hasfloor){
                render_char(x,y,Fancy_Char(L'.',15));
            } else {
                render_char_bg(x,y,Fancy_Char(L' ',0),3);
            }
        }
    }
}

Chunk::Chunk(){
    //posx = 0;
    //posy = 0;
    //posz = 0;
    biome = "j";
    for (int i = 0; i < CHUNK_WIDTH; i++){
        for (int j = 0; j< CHUNK_WIDTH; j++){
            for (int k = 0; k < CHUNK_DEPTH; k++){
                tiles[i][j][k] = Tile(0,1,0,0);
            }
        }
    }
    tiles[1][2][0] = Tile(0,1,1,0); // stair up on tile at position (1,2).
}

Tile::Tile(bool w, bool f, bool u, bool d){
    haswall = w; hasfloor = f; stairup = u; stairdown = d;
}