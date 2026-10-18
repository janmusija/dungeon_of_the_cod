//
// worldgen/biome/biome_lookup.cpp
// 2026-10-17
// dungeon_of_the_cod
//
#include "worldgen/biome/biome_lookup.h"

std::string biome_lookup(float elevation, float temp, float rainfall, float alignment, float magic, float sealevel){
    const float BEACHFUZZ = 0.05;
    const float FREEZING = -0.25;
    const float HOT = 0.25;
    const float LOWLYING = sealevel + 0.15;
    const float MTN = sealevel + 0.27;
    const float V_WET = 0.85;
    const float WET = 0.7;
    const float DRY = 0.3;
    const float V_DRY = 0.15;
    bool ocean = false;
    std::string name = "default";
    // compare elevation to sea level
    if (elevation < sealevel){
        ocean = true;
        // oceans
        if (temp <= FREEZING) {
            name = "cold_ocean";
        }
        else if (temp <= HOT) {
            name = "ocean";
        }
        else name = "hot_ocean";
    } else if (elevation <= sealevel + BEACHFUZZ) {
        // beaches
        if (rainfall <= V_DRY){
            if (temp >= HOT){
                name = "hot_desert";
            }
            else name = "cold_desert";
        }
        else if (temp <= FREEZING) {
            name = "frozen_beach";
        }
        else if (rainfall >= V_WET){
            if (temp >= HOT){
                name = "tropical_rainforest";
            }
            else name = "swamp";
        }
        else name = "beach";
    } else if (elevation <= LOWLYING) { // low-lying areas that are not beaches
        if (rainfall >= V_WET){
            if (temp >= HOT){
                name = "tropical_rainforest";
            }
            else if (temp <= FREEZING){
                name = "tundra";
            }
            else name = "swamp";
        }
        else if (rainfall <= DRY){
            if (temp >= HOT){
                name = "hot_desert";
            }
            else if (temp <= FREEZING){
                name = "tundra";
            }
            else name = "cold_desert";
        }
        else if (rainfall < 0.5){
            if (temp >= HOT){
                name = "savanna";
            }
            else if (temp <= FREEZING){
                name = "tundra";
            }
            else name = "grassland";
        }
        else if (rainfall < V_WET){
            if (temp <= FREEZING){
                name = "taiga";
            }
            else name = "forest";
        }
    } else if (elevation <= MTN) {
        if (rainfall <= DRY){
            if (temp >= HOT){
                return "hot_steppe";
            }
            else if (temp <= FREEZING){
                name = "tundra";
            }
            else name = "cold_steppe";
        }
        else if (rainfall <= WET-0.1){
            if (temp >= HOT){
                name = "savanna";
            }
            else if (temp <= FREEZING){
                name = "tundra";
            }
            else name = "grassland";
        }
        else if (rainfall <= V_WET){
            if (temp <= FREEZING + 0.1){
                name = "taiga";
            }
            else name = "forest";
        }
        else if (temp > FREEZING+0.1){
            name = "temperate_rainforest";
        }
        else if (temp <= FREEZING-0.05){
            name = "tundra";
        }
        else name = "taiga";
    } else {
        // mountains
        name = "mountain";
    }

    if (magic >= 0.7 || alignment * magic < -1){
        if (alignment-magic < -1.2){
            // evil, enchanted areas
            if (name == "ocean") name = "evil_ocean";
            if (name == "cold_ocean") name = "evil_cold_ocean";
            if (name == "hot_ocean") name = "evil_hot_ocean";
            if (name == "mountain") name = "evil_mountain";
            if (name == "tundra") name = "evil_tundra";
        }
    }

    /*if (alignment < -2.0 && !ocean){
        name = "hell";
    }*/

    return name;
}

RGB biome_color(std::string s){
    if (s == "ocean") {return RGB(0,0,0.3);}
    if (s == "evil_ocean") {return RGB(0.3,0,0);}
    if (s == "cold_ocean") {return RGB(0.2,0.2,0.3);}
    if (s == "evil_cold_ocean") {return RGB(0.5,0.2,0.3);}
    if (s == "hot_ocean") {return RGB(0.2,0,0.3);}
    if (s == "evil_hot_ocean") {return RGB(0.4,0,0.3);}
    if (s == "frozen_beach") {return RGB(0.5,0.5,0.3);}
    if (s == "beach") {return RGB(0.5,0.5,0);}
    if (s == "swamp") {return RGB(0,0.3,0);}
    if (s == "tropical_rainforest") {return RGB(0,0.1,0.9);}
    if (s == "savanna") {return RGB(0.5,0.5,0.8);}
    if (s == "temperate_rainforest") {return RGB(0,0.9,0);}
    if (s == "forest") {return RGB(0,0.7,0);}
    if (s == "taiga") {return RGB(0,0.6,0.4);}
    if (s == "tundra") {return RGB(1,1,1);}
    if (s == "evil_tundra") {return RGB(0.5,1,1);}
    if (s == "grassland") {return RGB(0.8,0.8,0);}
    if (s == "mountain") {return RGB(0.7,0.7,0.7);}
    if (s == "evil_mountain") {return RGB(0.9,0.7,0.7);}
    if (s == "hot_desert") {return RGB(0.8,0,0);}
    //if (s == "hell") {return RGB(0.6,0,0);}
    if (s == "cold_desert") {return RGB(0.8,0.5,0.5);}
    if (s == "hot_steppe") {return RGB(0.8,0.4,0);}
    if (s == "cold_steppe") {return RGB(0.8,0.65,0.5);}
    return RGB(0,0,0);
}