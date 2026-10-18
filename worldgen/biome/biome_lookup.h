//
// worldgen/biome/biome_lookup.h
// 2026-10-17
// dungeon_of_the_cod
//

#ifndef biome_lookup_h
#define biome_lookup_h

#include <string>
#include "tools/image.h"

std::string biome_lookup(float elevation, float temp, float rainfall, float alignment, float magic, float sealevel);
RGB biome_color(std::string s);

#endif