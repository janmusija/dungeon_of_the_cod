//
// worldgen/biome/biome.h
// 2026-10-17
// dungeon_of_the_cod
//

#ifndef biome_h
#define biome_h
#include "tools/PerlinNoise.hpp"
#include <random>
#include "tools/image.h"

class Terrain {
    public:
    siv::PerlinNoise __ELEVATION; // low to high
    siv::PerlinNoise __RAINFALL_VARIATION; // dry to wet
    siv::PerlinNoise __TEMPERATURE_VARIATION; // cold to hot
    siv::PerlinNoise __ALIGNMENT; // good to evil
    siv::PerlinNoise __MAGIC; // mundane to enchanted

    int max_elevation; // corresponding to noise value of 1. max elevation of terrain
    int min_elevation; // corresponding to noise value of 0
    int sea_level; // level at which water Exists

    float __SEA_FLOAT;

    uint32_t __SEED;

    float __ELEVATION_SCALE;
    float __RAIN_SCALE;
    float __TEMP_SCALE;
    float __ALIGNMENT_SCALE;
    float __MAGIC_SCALE;

    float latitude_behavior_period = 16;
    float latitude_behavior_displacement;

    const static int __ELEVATION_OCTAVES = 11;
    const static int __RAIN_OCTAVES = 3;
    const static int __TEMP_OCTAVES = 4;
    const static int __ALIGNMENT_OCTAVES = 3;
    const static int __MAGIC_OCTAVES = 3;

    float TILE_SCALE; // size of an individual tile on the map in units

    float ELEVATION(float x, float y, int lod = __ELEVATION_OCTAVES); // inputs are in map units
    float RAINFALL(float x, float y);
    float TEMPERATURE(float x, float y);
    float ALIGNMENT(float x, float y);
    float MAGIC(float x, float y);

    float SURFACE_ELEVATION(float x, float y, int lod = __ELEVATION_OCTAVES); // including the ocean

    Terrain(uint32_t seed);

    void export_images(int32_t centerx, int32_t centery, int scale);
};

#endif