//
// worldgen/biome/sky_islands.h
// 2026-10-17
// dungeon_of_the_cod
//

#ifndef sky_worldgen_h
#define sky_worldgen_h
#include "worldgen/biome/biome.h"

class Sky_Island_Terrain : public Terrain {
    public:
    siv::PerlinNoise __SURFACE_SHIFT;
    siv::PerlinNoise __SURFACE_THICKNESS;

    float __SURFACE_SCALE;
    float __SURFACE_CUTOFF;
    float __UNEVENNESS;

    const static int __SURFACE_OCTAVES = 11;

    float SURFACE_SHIFT(float x, float y, int lod = __SURFACE_OCTAVES); // inputs are in map units
    float SURFACE_THICKNESS(float x, float y, int lod = __SURFACE_OCTAVES);
    void SURFACE_INTERVAL(float x, float y, float& top, float& bottom, int lod = __SURFACE_OCTAVES);

    Sky_Island_Terrain(uint32_t seed);

    void export_images(int32_t centerx, int32_t centery, int scale, std::string dim_id = "");
};

class Heaven_Terrain : public Sky_Island_Terrain {
    public:
    Heaven_Terrain(uint32_t seed);
};

class Hell_Terrain : public Sky_Island_Terrain {
    public:
    Hell_Terrain(uint32_t seed);
};

class Outside_Terrain : public Sky_Island_Terrain {
    public:
    Outside_Terrain(uint32_t seed);
};

#endif