//
// worldgen/biome/biome.cpp
// 2026-10-17
// dungeon_of_the_cod
//


#include "worldgen/biome/sky_islands.h"
#include "worldgen/biome/biome_lookup.h"
#include <cmath>

float Sky_Island_Terrain::SURFACE_SHIFT(float x, float y, int lod){
    return __SURFACE_SHIFT.octave2D_11(x * __SURFACE_SCALE, y * __SURFACE_SCALE, lod);
}

float Sky_Island_Terrain::SURFACE_THICKNESS(float x, float y, int lod){
    float t = __SURFACE_THICKNESS.octave2D_01(x * __SURFACE_SCALE, y * __SURFACE_SCALE, lod);
    if (t <= __SURFACE_CUTOFF){
        return 0;
    }
    else {
        return (t - __SURFACE_CUTOFF)/(1-__SURFACE_CUTOFF);
    }
}

void Sky_Island_Terrain::SURFACE_INTERVAL(float x, float y, float& top, float& bottom, int lod){
    float th = SURFACE_THICKNESS(x,y,lod);
    if (th <= 0) {
        top = NAN;
        bottom = NAN;
    } else {
        float p = 0.5 + (SURFACE_SHIFT(x,y,lod) * (__UNEVENNESS/2));
        top = p + (th * (1-__UNEVENNESS)/2);
        bottom = p - (th * (1-__UNEVENNESS)/2);
    }
}

Sky_Island_Terrain::Sky_Island_Terrain(uint32_t seed) : Terrain(seed){
    std::mt19937 mt(seed); 
    mt.discard(21);
    __SURFACE_SHIFT = siv::PerlinNoise { mt() };
    __SURFACE_THICKNESS = siv::PerlinNoise { mt() };
    __SURFACE_CUTOFF = 0.5;
    __SURFACE_SCALE = 1.0;
    __UNEVENNESS = 0.5;
}

void Sky_Island_Terrain::export_images(int32_t centerx, int32_t centery, int scale, std::string dim_id){
    std::string fnb;
    std::stringstream filenamebase;
    Image image{ 512, 512 };
    filenamebase << "img/" << __SEED << 'x' << centerx << 'y' << centery << 's' << scale << dim_id;
    filenamebase >> fnb;
    // elevation
    {
        std::stringstream ss;
        ss << fnb << "sky_island_elevation" << ".bmp";
        for (std::int32_t y = 0; y < image.height(); ++y)
		{
			for (std::int32_t x = 0; x < image.width(); ++x)
			{
                int scaled_x = (x - image.width()/2) * scale + centerx; 
                int scaled_y = (y - image.height()/2) * scale + centery;
                float t; float  b;
                SURFACE_INTERVAL(scaled_x*TILE_SCALE, scaled_y*TILE_SCALE,t,b);
                if (std::isnan(t)){
                    const RGB color(0, 0, 0);
                    image.set(x, y, color);
                } else{
                    const RGB color(t,t,t);
                    image.set(x, y, color);
                }
			}
		}
        if (image.saveBMP(ss.str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
		}
    }
}

Heaven_Terrain::Heaven_Terrain(uint32_t seed) : Sky_Island_Terrain(seed){
    __SURFACE_CUTOFF = 0.4;
    __SURFACE_SCALE = 1.0;
    __UNEVENNESS = 0.2;
}

Hell_Terrain::Hell_Terrain(uint32_t seed) : Sky_Island_Terrain(seed){
    __SURFACE_CUTOFF = 0.5;
    __SURFACE_SCALE = 1.0;
    __UNEVENNESS = 0.8;
}

Outside_Terrain::Outside_Terrain(uint32_t seed) : Sky_Island_Terrain(seed){
    __SURFACE_CUTOFF = 0.7;
    __SURFACE_SCALE = 1.0;
    __UNEVENNESS = 0.5;
}